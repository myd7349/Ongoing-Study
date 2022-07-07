<Query Kind="Statements" />

for (int vk = 0; vk <= 256; ++vk)
{
    var wpfKeyDefined = Enum.IsDefined(typeof(System.Windows.Input.Key), vk);
    var winformsKeyDefined = Enum.IsDefined(typeof(System.Windows.Forms.Keys), vk);
    
    if (wpfKeyDefined && winformsKeyDefined)
    {
        var wpfName = ((System.Windows.Input.Key)vk).ToString();
        var winformsName = ((System.Windows.Forms.Keys)vk).ToString();

        if (wpfName == winformsName)
            Console.WriteLine("VK {0} is defined both in WPF and WinForms, with identical name {1}.", vk, wpfName);
        else
            Console.WriteLine("VK {0} is defined both in WPF and WinForms, with different name {1}(WPF), {2}(WinForms).", vk, wpfName, winformsName);
    }
    else if (!wpfKeyDefined && !winformsKeyDefined)
    {
        Console.WriteLine("VK {0} not defined.", vk);
    }
    else
    {
        if (wpfKeyDefined)
        {
            Console.WriteLine("VK {0} is defined in WPF({1}), but is not defined in WinForms.",
                vk, (System.Windows.Input.Key)vk);
        }
        else
        {
            Console.WriteLine("VK {0} is defined in WinForms({1}), but is not defined in WPF.",
                vk, (System.Windows.Forms.Keys)vk);
        }
    }
}
