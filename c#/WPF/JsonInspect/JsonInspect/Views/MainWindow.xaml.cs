using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Windows.Input;

using Microsoft.Win32;

using Newtonsoft.Json;

using static Common.JsonHelper;

using JsonInspect.ViewModels;

using FileSystem = System.IO.Path;

namespace JsonInspect.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            viewModel_ = DataContext as MainWindowViewModel;
            Debug.Assert(viewModel_ != null);

            viewModel_.PropertyChanged += ViewModel_PropertyChanged;
        }

        public MainWindow(string filePath)
            : this()
        {
            OpenFile(filePath);
        }

        private void ViewModel_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(viewModel_.Indented))
            {
                if (!string.IsNullOrEmpty(textEditor_.Text) && viewModel_.Indented != null)
                {
                    try
                    {
                        var json = FormatJson(textEditor_.Text, viewModel_.Indented.Value);
                        textEditor_.Text = json;
                    }
                    catch (JsonReaderException ex)
                    {
                    }
                }
            }
        }

        private void Window_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.Text) || e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effects = DragDropEffects.Copy;
            else
                e.Effects = DragDropEffects.None;
        }

        private void Window_DragLeave(object sender, DragEventArgs e)
        {
        }

        private void Window_Drop(object sender, DragEventArgs e)
        {
            string jsonFilePath = null;
            if (e.Data.GetDataPresent(DataFormats.Text))
            {
                jsonFilePath = (string)e.Data.GetData(DataFormats.Text);
            }
            else if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                var fileNames = (string[])e.Data.GetData(DataFormats.FileDrop);
                jsonFilePath = fileNames[0];
            }

            if (string.IsNullOrEmpty(jsonFilePath) || !File.Exists(jsonFilePath))
                return;

            OpenFile(jsonFilePath);
        }

        private void openButton__Click(object sender, RoutedEventArgs e)
        {
            var filters = new[]
            {
                "JSON Files|*.json",
                "BSON Files|*.bson",
                "All Files|*.*",
            };

            var openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = string.Join("|", filters);

            if (openFileDialog.ShowDialog() == true)
                OpenFile(openFileDialog.FileName);
        }

        private void saveButton__Click(object sender, RoutedEventArgs e)
        {
            SaveFile();
        }

        private void saveAsButton__Click(object sender, RoutedEventArgs e)
        {
            SaveFile(true);
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            var result = CheckSave();
            if (result == MessageBoxResult.Yes)
            {
                SaveFile();
            }
            else if (result == MessageBoxResult.Cancel)
            {
                e.Cancel = true;
                return;
            }

            base.OnClosing(e);
        }

        private void OpenFile(string jsonFilePath)
        {
            var result = CheckSave();
            if (result == MessageBoxResult.Yes)
                SaveFile();
            else if (result == MessageBoxResult.Cancel)
                return;

            string json = string.Empty;
            try
            {
                Cursor = Cursors.Wait;
                ForceCursor = true;

                var isBson = string.Compare(FileSystem.GetExtension(jsonFilePath), ".bson", true) == 0;
                if (isBson)
                {
                    try
                    {
                        json = LoadBson(jsonFilePath, viewModel_.Indented);
                        viewModel_.IsBson = true;
                    }
                    catch (JsonException)
                    {
                        json = viewModel_.Indented == null ?
                            LoadJson(jsonFilePath) :
                            LoadJson(jsonFilePath, viewModel_.Indented);
                        viewModel_.IsBson = false;
                    }
                }
                else
                {
                    try
                    {
                        json = viewModel_.Indented == null ?
                            LoadJson(jsonFilePath) :
                            LoadJson(jsonFilePath, viewModel_.Indented);
                        viewModel_.IsBson = false;
                    }
                    catch (JsonException)
                    {
                        json = LoadBson(jsonFilePath, viewModel_.Indented);
                        viewModel_.IsBson = true;
                    }
                }


                viewModel_.FilePath = jsonFilePath;
                textEditor_.Text = json;
                textEditor_.IsModified = false;
            }
            catch (JsonException ex)
            {
                MessageBox.Show(
                    $"\"{jsonFilePath}\" is not a valid JSON/BSON file.\r\n{ex.Message}",
                    "Error:",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }
            finally
            {
                Cursor = Cursors.Arrow;
                ForceCursor = false;
            }
        }

        private MessageBoxResult CheckSave()
        {
            if (textEditor_.IsModified)
            {
                var message = string.Empty;
                if (File.Exists(viewModel_.FilePath))
                    message += $"File \"{viewModel_.FilePath}\" has been modified. ";

                message += "Do you want to save current changes or not?";
                return MessageBox.Show(
                    message,
                    "Confirm:",
                    MessageBoxButton.YesNoCancel,
                    MessageBoxImage.Warning,
                    MessageBoxResult.Cancel);
            }
            else
            {
                return MessageBoxResult.No;
            }
        }

        private void SaveFile(bool saveAs = false)
        {
            string filePath = saveAs ? null : viewModel_.FilePath;

            if (string.IsNullOrEmpty(filePath))
            {
                var filters = new List<string>
                {
                    "JSON Files|*.json",
                    "BSON Files|*.bson",
                    "Text Files|*.txt",
                };
                var filterIndex = viewModel_.IsBson ? 2 : 1;

                if (!string.IsNullOrEmpty(viewModel_.FilePath))
                {
                    var fileExtension = FileSystem.GetExtension(viewModel_.FilePath);
                    if (string.Compare(fileExtension, ".json", true) != 0 &&
                        string.Compare(fileExtension, ".bson", true) != 0 &&
                        string.Compare(fileExtension, ".txt", true) != 0 &&
                        fileExtension.Length >= 2)
                    {
                        var newFilter =
                            $"{char.ToUpper(fileExtension[1])}{fileExtension.Substring(2)} Files|*{fileExtension}";
                        filters.Add(newFilter);
                    }
                }

                var saveFileDialog = new SaveFileDialog();
                saveFileDialog.Title = saveAs ? "Save as:" : "Save File:";

                if (!string.IsNullOrEmpty(viewModel_.FilePath))
                    saveFileDialog.FileName = FileSystem.GetFileNameWithoutExtension(viewModel_.FilePath);

                saveFileDialog.OverwritePrompt = true;
                saveFileDialog.Filter = string.Join("|", filters);
                saveFileDialog.FilterIndex = filterIndex; // 1-based

                if (saveFileDialog.ShowDialog() == true)
                    filePath = saveFileDialog.FileName;
                else
                    return;
            }

            var isBson = false;
            if (!string.IsNullOrEmpty(viewModel_.FilePath) && !saveAs)
                isBson = viewModel_.IsBson;
            else
                isBson = string.Compare(FileSystem.GetExtension(filePath), ".bson", true) == 0;

            if (isBson)
                StoreBson(filePath, textEditor_.Text);
            else
                StoreJson(filePath, textEditor_.Text, viewModel_.Indented);

            viewModel_.FilePath = filePath;
            viewModel_.IsBson = isBson;
            textEditor_.IsModified = false;
        }

        private MainWindowViewModel viewModel_;
    }
}


// References:
// https://github.com/ElinamLLC/SvgViewer
// https://github.com/mattleibow/SkiaSharpFiddle/blob/master/SkiaSharpFiddle/MainWindow.xaml.cs
// [How to set/reset Three-state checkbox value in WPF](https://stackoverflow.com/questions/4778230/how-to-set-reset-three-state-checkbox-value-in-wpf)
// [AvalonEdit : Textstate](https://stackoverflow.com/questions/33390456/avalonedit-textstate)
