## Issue this repo reproduces:

When building for Release, dispatching a command through `UIManager.dispatchViewManagerCommand` only calls into native code after the UI updates for some reason:

```C++
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
```

```JavaScript
          <Text>Button to change the RNSimple contents after 1 second. Works on Debug. On Release, it waits for an UI change before sending the command.</Text>
          <Button title="ChangeText" onPress={() => {
            numberOfPresses++;
            let currentPresses = numberOfPresses;
            setTimeout( () => {
              UIManager.dispatchViewManagerCommand(
                nativeCompHandle,
                UIManager.getViewManagerConfig('RNSimple').Commands.changeText,
                [ "The button has been pressed " + currentPresses + " times." ]
              );
            }, 2000);
          }} />
          <RNSimple ref={ref => {nativeCompHandle = ReactNative.findNodeHandle(ref)}} style={{flex:1}}/>
```

## How to run

```bash
git clone https://github.com/jaimecbernardo/reproduce-rnw64-release-dispatch-command-issue
cd reproduce-rnw64-release-dispatch-command-issue
yarn
npx react-native run-windows
```

Expected behavior on both Debug and Release after clicking the button and waiting 2 seconds:

![image](https://user-images.githubusercontent.com/26118718/113750990-53b50380-9703-11eb-823c-6b4109a43fc1.png)

When building for Release, clicking the button won't change the text after 2 seconds:
```bash
npx react-native run-windows --release
```

![image](https://user-images.githubusercontent.com/26118718/113751420-d76ef000-9703-11eb-8cbd-09695cf84f0e.png)

The text will only change after doing something that forces the UI to update, like clicking the button again.

## How the sample was built

```bash
npx react-native init ReproduceRNWReleaseBug --template react-native@^0.64.0
cd ReproduceRNWReleaseBug
npx react-native-windows-init --overwrite
```

Then the Native Module code was added and `App.js` was changed to call into it.  
This commit has those changes:  
https://github.com/jaimecbernardo/reproduce-rnw64-release-dispatch-command-issue/commit/9fd9305d7775bcf33dcdbc38740be2b778159035
