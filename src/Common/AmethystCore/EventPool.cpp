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

#include "EventPool.hpp"

using namespace Amethyst::Core;

EventPool::EventPool() :
    pool(POOL_SIZE)
{

}

Event *EventPool::BorrowEvent()
{
    return pool.malloc();
}

void EventPool::ReturnEvent(Event *ev)
{
    pool.free(ev);
}
