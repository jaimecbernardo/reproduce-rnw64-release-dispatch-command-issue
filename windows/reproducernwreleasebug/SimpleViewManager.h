#pragma once
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"

namespace winrt::reproducernwreleasebug::implementation
{

    class SimpleViewManager : public winrt::implements<
        SimpleViewManager,
        winrt::Microsoft::ReactNative::IViewManager,
        winrt::Microsoft::ReactNative::IViewManagerWithCommands>
    {
    public:
        SimpleViewManager() = default;

        // IViewManager
        winrt::hstring Name() noexcept;
        winrt::Windows::UI::Xaml::FrameworkElement CreateView() noexcept;

        // IViewManagerWithCommands
        winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> Commands() noexcept;

        void DispatchCommand(
            winrt::Windows::UI::Xaml::FrameworkElement const& view,
            winrt::hstring const& commandId,
            winrt::Microsoft::ReactNative::IJSValueReader const& commandArgsReader) noexcept;
    };
}
