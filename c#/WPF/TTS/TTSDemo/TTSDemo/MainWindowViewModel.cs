using System.Collections.ObjectModel;
using System.Speech.Synthesis;

using CommunityToolkit.Mvvm.ComponentModel;

namespace TTSDemo
{
    public partial class MainWindowViewModel : ObservableObject
    {
        public MainWindowViewModel()
        {
            textToSpeak_ = "Ground control to major Tom!";

            Speaker = new SpeechSynthesizer();

            InstalledVoices = Speaker.GetInstalledVoices();

            Speaker.SetOutputToDefaultAudioDevice();
        }

        public string TextToSpeak
        {
            get => textToSpeak_;
            set => SetProperty(ref textToSpeak_, value);
        }

        public SpeechSynthesizer Speaker { get; }

        public ReadOnlyCollection<InstalledVoice> InstalledVoices { get; }

        public InstalledVoice SelectedVoice
        {
            get => selectedVoice_;

            set
            {
                if (SetProperty(ref selectedVoice_, value))
                    Speaker.SelectVoice(selectedVoice_.VoiceInfo.Name);
            }
        }

        public int Volume
        {
            get => Speaker.Volume;

            set
            {
                if (Speaker.Volume != value)
                {
                    Speaker.Volume = value;
                    OnPropertyChanged();
                }
            }
        }

        public void Speak()
        {
            Speaker.Speak(textToSpeak_);
        }

        private string textToSpeak_;
        private InstalledVoice selectedVoice_;
    }
}


// References:
// [计算照片的面积（WPF篇）](https://www.cnblogs.com/tcjiaan/p/5077863.html)
// https://docs.microsoft.com/en-us/dotnet/api/system.speech.synthesis.speechsynthesizer?view=netframework-4.8
