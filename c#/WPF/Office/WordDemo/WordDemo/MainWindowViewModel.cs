using System.IO;

using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;
using MvvmDialogs.FrameworkDialogs.OpenFile;
using MvvmDialogs.FrameworkDialogs.SaveFile;

namespace WordDemo
{
    class MainWindowViewModel : ObservableObject
    {
        public MainWindowViewModel()
        {
            dialogService_ = new DialogService();
        }

        public string? WordFilePath
        {
            get => wordFilePath_;

            set
            {
                if (SetProperty(ref wordFilePath_, value))
                    ExportAsXpsCommand.NotifyCanExecuteChanged();
            }
        }

        public IRelayCommand SelectWordFileCommand => new RelayCommand(SelectWordFile);

#if false
        public IRelayCommand ExportAsXpsCommand => new RelayCommand(
            ExportAsXps, () => !string.IsNullOrEmpty(WordFilePath));
#elif false
        public IRelayCommand ExportAsXpsCommand => new RelayCommand(
            ExportAsXps, CanExportAsXps);
#else
        public IRelayCommand ExportAsXpsCommand =>
            exportAsXpsCommand_ ??
            (exportAsXpsCommand_ = new RelayCommand(ExportAsXps, CanExportAsXps));
#endif

        private void SelectWordFile()
        {
            var openFileDialogSettings = new OpenFileDialogSettings
            {
                Filter = "Word files (*.docx)|*.docx|All files (*.*)|*.*"
            };

            var result = dialogService_.ShowOpenFileDialog(this, openFileDialogSettings);
            if (result == true)
            {
                WordFilePath = openFileDialogSettings.FileName;
            }
        }

        private bool CanExportAsXps()
        {
            return !string.IsNullOrEmpty(WordFilePath);
        }
        
        private void ExportAsXps()
        {
            var saveFileDialogSettings = new SaveFileDialogSettings
            {
                Filter = "XPS files (*.xps)|*.xps",
                OverwritePrompt = true,
                AddExtension = true,
                FileName = Path.GetFileNameWithoutExtension(WordFilePath)!,
            };

            var result = dialogService_.ShowSaveFileDialog(this, saveFileDialogSettings);
            if (result == true)
                ExportAsXps(WordFilePath!, saveFileDialogSettings.FileName);
        }
        
        private void ExportAsXps(string wordFilePath, string xpsFilePath)
        {
            var wordApplication = new Microsoft.Office.Interop.Word.Application();
            var wordDocument = wordApplication.Documents.Open(wordFilePath);
            wordDocument.ExportAsFixedFormat(
                xpsFilePath,
                Microsoft.Office.Interop.Word.WdExportFormat.wdExportFormatXPS);
            wordDocument.Close();
            wordApplication.Quit();
        }

        private readonly IDialogService dialogService_ = null!;

        private IRelayCommand? exportAsXpsCommand_;
        
        private string? wordFilePath_;
    }
}


// References:
// [XPS - Printing documents with images](https://stackoverflow.com/questions/10278041/xps-printing-documents-with-images)
// [Saving Word 2007 Documents to PDF and XPS Formats](https://learn.microsoft.com/en-us/previous-versions/office/developer/office-2007/bb412305(v=office.12)?redirectedfrom=MSDN)
