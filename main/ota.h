#ifndef _OTA_H
#define _OTA_H

#include <functional>
#include <string>
#include <map>

#include <esp_err.h>
#include "board.h"
#include "server/giz_api.h"

class Ota {
public:
    Ota();
    ~Ota();

    void SetHeader(const std::string& key, const std::string& value) {}
    bool CheckVersion();
    esp_err_t Activate() { return ESP_OK; }
    bool HasActivationChallenge() { return false; }
    bool HasNewVersion() { return has_new_version_; }
    bool HasMqttConfig() { return false; }
    bool HasWebsocketConfig() { return false; }
    bool HasActivationCode() { return false; }
    bool HasServerTime() { return false; }
    void StartUpgrade(std::function<void(int progress, size_t speed)> callback);
    void MarkCurrentVersionValid();

    const std::string& GetFirmwareVersion() const { return firmware_version_; }
    const std::string& GetCurrentVersion() const { return current_version_; }
    const std::string& GetActivationMessage() const { return activation_message_; }
    const std::string& GetActivationCode() const { return activation_code_; }
    const std::string& GetCheckVersionUrl() const { return check_version_url_; }

private:
    std::string check_version_url_;
    std::string activation_message_;
    std::string activation_code_;
    bool has_new_version_ = false;
    bool has_mqtt_config_ = false;
    bool has_websocket_config_ = false;
    bool has_server_time_ = false;
    bool has_activation_code_ = false;
    bool has_serial_number_ = false;
    bool has_activation_challenge_ = false;
    std::string current_version_;
    std::string firmware_version_;
    std::string firmware_url_;
    std::string activation_challenge_;
    std::string serial_number_;
    int activation_timeout_ms_ = 30000;
    std::map<std::string, std::string> headers_;

    void Upgrade(const std::string& firmware_url);
    std::function<void(int progress, size_t speed)> upgrade_callback_;
    std::vector<int> ParseVersion(const std::string& version);
    bool IsNewVersionAvailable(const std::string& currentVersion, const std::string& newVersion);
    std::string GetActivationPayload() { return "{}"; }
    Http* SetupHttp() { return nullptr; }
};

#endif // _OTA_H
