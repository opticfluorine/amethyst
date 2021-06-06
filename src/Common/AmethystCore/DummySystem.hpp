/*
 * Amethyst MMORPG Engine
 * Copyright 2021 opticfluorine
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __AMETHYSTCORE_DUMMYSYSTEM_HPP__
#define __AMETHYSTCORE_DUMMYSYSTEM_HPP__

#include "CoreEvents.hpp"
#include "System.hpp"

namespace Amethyst {
namespace Core {

    class DummySystem;
    using _DummySystem_Base = System<DummySystem, EventId::CORE_SHUTDOWN>;

    /**@brief Example system for initial testing.
     */
    class DummySystem final : public _DummySystem_Base
    {
    public:
        DummySystem();
        virtual ~DummySystem();

        // Mixin default event handlers with error logging.
        SYSTEM_DEFAULT_ONEVENT;

    };

    /**@brief Called when a shutdown event is received.
     */
    template<>
    void DummySystem::OnEvent<EventId::CORE_SHUTDOWN>()
    {

    }

}
}

#endif
