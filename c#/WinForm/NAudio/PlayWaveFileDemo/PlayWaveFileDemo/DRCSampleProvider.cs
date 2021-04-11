namespace PlayWaveFileDemo
{
    using NAudio.Wave;
    using NAudio.Wave.SampleProviders;

    class DRCSampleProvider : SampleProviderConverterBase
    {
        public DRCSampleProvider(IWaveProvider waveProvider)
            : base(waveProvider)
        {
            volumeSampleProvider_ = new VolumeSampleProvider(waveProvider.ToSampleProvider());
            drcSampleProvider_ = new SimpleCompressorEffect(volumeSampleProvider_);
        }

        public DRCSampleProvider(AudioFileReader audioFileReader)
            : base(audioFileReader)
        {
            audioFileReader_ = audioFileReader;
            drcSampleProvider_ = new SimpleCompressorEffect(audioFileReader_);
        }

        public double MakeUpGain
        {
            get => drcSampleProvider_.MakeUpGain;
            set => drcSampleProvider_.MakeUpGain = value;
        }

        public double Threshold
        {
            get => drcSampleProvider_.Threshold;
            set => drcSampleProvider_.Threshold = value;
        }

        public double Ratio
        {
            get => drcSampleProvider_.Ratio;
            set => drcSampleProvider_.Ratio = value;
        }

        public double Attack
        {
            get => drcSampleProvider_.Attack;
            set => drcSampleProvider_.Attack = value;
        }

        public double Release
        {
            get => drcSampleProvider_.Release;
            set => drcSampleProvider_.Release = value;
        }

        public bool Enabled
        {
            get => drcSampleProvider_.Enabled;
            set => drcSampleProvider_.Enabled = value;
        }

        public float Volume
        {
            get
            {
                if (volumeSampleProvider_ != null)
                    return volumeSampleProvider_.Volume;
                else
                    return audioFileReader_.Volume;
            }

            set
            {
                if (volumeSampleProvider_ != null)
                    volumeSampleProvider_.Volume = value;
                else
                    audioFileReader_.Volume = value;
            }
        }

        public override int Read(float[] buffer, int offset, int count)
        {
            return drcSampleProvider_.Read(buffer, offset, count);
        }

        private VolumeSampleProvider volumeSampleProvider_;
        private AudioFileReader audioFileReader_;
        private SimpleCompressorEffect drcSampleProvider_;
    }
}


// References:
// https://github.com/naudio/NAudio/blob/master/NAudio.Core/Wave/WaveProviders/Wave16toFloatProvider.cs
// https://github.com/naudio/NAudio/blob/master/NAudio.Core/Dsp/SimpleCompressor.cs
// https://github.com/naudio/NAudio/blob/master/NAudio.Core/Wave/SampleProviders/Pcm32BitToSampleProvider.cs
// [How can i make the sound louder with Naudio c#?](https://stackoverflow.com/questions/49067902/how-can-i-make-the-sound-louder-with-naudio-c)
// [How to convert []Int16 to []float using C# and NAudio?](https://stackoverflow.com/questions/19867467/how-to-convert-int16-to-float-using-c-sharp-and-naudio)
// [BufferedWaveProvider converted for use in WaveMixerStream32 lowers pitch of audio](https://stackoverflow.com/questions/18475229/bufferedwaveprovider-converted-for-use-in-wavemixerstream32-lowers-pitch-of-audi)
// [Help with dynamic range compression function (audio)](https://stackoverflow.com/questions/2908104/help-with-dynamic-range-compression-function-audio)
// https://github.com/markheath/skypevoicechanger/blob/master/SkypeVoiceChanger/Effects/FastAttackCompressor1175.cs
// https://github.com/naudio/NAudio/blob/master/NAudio.Core/Wave/WaveStreams/SimpleCompressorStream.cs
// https://github.com/naudio/NAudio/blob/fb35ce8367f30b8bc5ea84e7d2529e172cf4c381/NAudio.Core/Wave/SampleProviders/SampleProviderConverters.cs
