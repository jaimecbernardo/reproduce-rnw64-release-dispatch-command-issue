#include "pch.h"
#include "ReactPackageProvider.h"
#include "NativeModules.h"
#include "SimpleViewManager.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::reproducernwreleasebug::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
    AddAttributedModules(packageBuilder);
    packageBuilder.AddViewManager(L"SimpleViewManager", []() { return winrt::make<SimpleViewManager>(); });
}

} // namespace winrt::reproducernwreleasebug::implementation
