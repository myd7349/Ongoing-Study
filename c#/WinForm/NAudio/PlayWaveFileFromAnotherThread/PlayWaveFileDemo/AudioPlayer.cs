namespace PlayWaveFileDemo
{
    using NAudio.Wave;

    public class AudioPlayer : WaveOut
    {
        public AudioPlayer(WaveFormat waveFormat)
        {
            bufferedWaveProvider_ = new BufferedWaveProvider(waveFormat)
            {
                DiscardOnBufferOverflow = true,
            };

            Init(bufferedWaveProvider_);
        }

        public void AddSamples(byte[] buffer, int offset, int count)
        {
            bufferedWaveProvider_.AddSamples(buffer, offset, count);
        }

        private BufferedWaveProvider bufferedWaveProvider_;
    }
}
