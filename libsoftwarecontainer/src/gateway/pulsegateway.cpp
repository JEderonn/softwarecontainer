/*
 *   Copyright (C) 2014 Pelagicore AB
 *   All rights reserved.
 */
#include <stdio.h>
#include "pulsegateway.h"

PulseGateway::PulseGateway() :
    Gateway(ID)
{
}

PulseGateway::~PulseGateway()
{
}

ReturnCode PulseGateway::readConfigElement(const JSonElement &element)
{
    bool enabled = false;
    element.read("audio", enabled);
    m_enableAudio |= enabled;
    return ReturnCode::SUCCESS;
}

bool PulseGateway::activateGateway()
{
    if (m_enableAudio) {
        log_debug() << "Audio will be enabled";
        const char *dir = getenv(PULSE_AUDIO_SERVER_ENVIRONMENT_VARIABLE_NAME);
        if (dir != nullptr) {
            log_info() << "enabling pulseaudio gateway. Socket location : " << dir;
            std::string path;
            ReturnCode result = getContainer()->bindMountFileInContainer(dir, SOCKET_FILE_NAME, path, false);
            if (isError(result)) {
                log_error() << "Could not bind mount pulseaudio socket in container";
                return false;
            }

            std::string unixPath = "unix:" + path;
            setEnvironmentVariable(PULSE_AUDIO_SERVER_ENVIRONMENT_VARIABLE_NAME, unixPath );
        } else {
            log_error() << "Should enable pulseaudio gateway, but " << std::string(PULSE_AUDIO_SERVER_ENVIRONMENT_VARIABLE_NAME) << " is not defined";
            return false;
        }
    } else {
        log_debug() << "Audio will be disabled";
    }
    return true;
}

bool PulseGateway::teardownGateway()
{
    return true;
}
