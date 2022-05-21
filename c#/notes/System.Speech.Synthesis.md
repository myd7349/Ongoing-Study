[计算照片的面积（WPF篇）](https://www.cnblogs.com/tcjiaan/p/5077863.html)

https://docs.microsoft.com/en-us/dotnet/api/system.speech.synthesis.speechsynthesizer?view=netframework-4.8

```csharp
Task.Run(() =>
{
    using (SpeechSynthesizer speaker = new SpeechSynthesizer())
    {
        speaker.SetOutputToDefaultAudioDevice();

        foreach (var voice in speaker.GetInstalledVoices())
        {
            speaker.SelectVoice(voice.VoiceInfo.Name);
            
            speaker.Speak("Hello, world!你好，世界！");
        }
    }
});
```
