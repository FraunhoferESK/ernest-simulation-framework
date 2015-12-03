#include <ernest/plugin_manager.hpp>
#include <ernest/osek_service.hpp>

namespace ERNEST
{

std::map<const std::string, IOsekService*> PluginManager::m_osekservice;

void PluginManager::RegisterOsekService(std::string id, IOsekService* service)
{
    m_osekservice[id] = service;
}

IOsekService* PluginManager::CreateOsekService(std::string id)
{
    IOsekService* service = m_osekservice[id];

    if (service != 0) {
        return m_osekservice[id]->Create();
    }

    return 0;
}

}  // ERNEST
