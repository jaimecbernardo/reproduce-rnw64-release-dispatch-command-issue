#include "pch.h"
#include "SimpleViewManager.h"

winrt::hstring winrt::reproducernwreleasebug::implementation::SimpleViewManager::Name() noexcept
{
    return L"RNSimple";
}

winrt::Windows::UI::Xaml::FrameworkElement winrt::reproducernwreleasebug::implementation::SimpleViewManager::CreateView() noexcept
{
    auto control = winrt::Windows::UI::Xaml::Controls::TextBlock();
    control.Text(L"This text hasn't been changed yet.");
    return control;
}

winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> winrt::reproducernwreleasebug::implementation::SimpleViewManager::Commands() noexcept
{
    auto commands = winrt::single_threaded_vector<hstring>();
    commands.Append(L"changeText");
    return commands.GetView();
}

void winrt::reproducernwreleasebug::implementation::SimpleViewManager::DispatchCommand(winrt::Windows::UI::Xaml::FrameworkElement const& view, winrt::hstring const& commandId, winrt::Microsoft::ReactNative::IJSValueReader const& commandArgsReader) noexcept
{
    auto commandArgs = winrt::Microsoft::ReactNative::JSValue::ReadArrayFrom(commandArgsReader);
    if (commandId == L"changeText")
    {
        if (auto control = view.try_as<winrt::Windows::UI::Xaml::Controls::TextBlock>())
        {
            control.Text(winrt::to_hstring(commandArgs[0].AsString()));
        }
    }
}
