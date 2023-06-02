#include "include/permission_handler_windows/permission_handler_windows_plugin.h"

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <flutter/encodable_value.h>

#include <memory>

namespace {

using namespace flutter;

class PermissionHandlerWindowsPlugin : public Plugin {
 public:
  static void RegisterWithRegistrar(PluginRegistrar* registrar);

  PermissionHandlerWindowsPlugin();

  virtual ~PermissionHandlerWindowsPlugin();

  // Disallow copy and move.
  PermissionHandlerWindowsPlugin(const PermissionHandlerWindowsPlugin&) = delete;
  PermissionHandlerWindowsPlugin& operator=(const PermissionHandlerWindowsPlugin&) = delete;

  // Called when a method is called on the plugin channel.
  void HandleMethodCall(const MethodCall<>&,
                        std::unique_ptr<MethodResult<>>);
};

// static
void PermissionHandlerWindowsPlugin::RegisterWithRegistrar(
    PluginRegistrar* registrar) {
  auto channel = std::make_unique<MethodChannel<>>(
    registrar->messenger(), "flutter.baseflow.com/permissions/methods",
    &StandardMethodCodec::GetInstance());

  std::unique_ptr<PermissionHandlerWindowsPlugin> plugin = std::make_unique<PermissionHandlerWindowsPlugin>();

  channel->SetMethodCallHandler(
    [plugin_pointer = plugin.get()](const auto& call, auto result) {
      plugin_pointer->HandleMethodCall(call, std::move(result));
    });

  registrar->AddPlugin(std::move(plugin));
}

PermissionHandlerWindowsPlugin::PermissionHandlerWindowsPlugin()= default;

PermissionHandlerWindowsPlugin::~PermissionHandlerWindowsPlugin() = default;

void PermissionHandlerWindowsPlugin::HandleMethodCall(
    const MethodCall<>& method_call,
    std::unique_ptr<MethodResult<>> result) {
  result->NotImplemented();
}

}  // namespace

void PermissionHandlerWindowsPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  PermissionHandlerWindowsPlugin::RegisterWithRegistrar(
      PluginRegistrarManager::GetInstance()
          ->GetRegistrar<PluginRegistrarWindows>(registrar));
}
