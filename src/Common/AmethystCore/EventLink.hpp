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

#ifndef __AMETHYSTCORE_EVENTLINK_HPP__
#define __AMETHYSTCORE_EVENTLINK_HPP__

#include <memory>

#include <boost/lockfree/queue.hpp>

#include "Events.hpp"

namespace Amethyst
{
namespace Core
{

class EventLoop;

/**\brief Provides linkage between an event loop and a system.
 */
class EventLink final
{
public:
    ~EventLink() { }
    EventLink(const EventLink&) = delete;
    EventLink& operator=(const EventLink&) = delete;

    /**@brief Checks whether an incoming event is pending.
     * @return true if pending, false otherwise.
     */
    inline bool EventPending() const { return false; }

    /**@brief Gets the next pending event.
     * @return Next pending event.
     */
    inline const Event &GetEvent() { return Event{}; }

    /**@brief Returns an event when processing is complete.
     */
    inline void ReturnEvent(const Event &ev) { }

protected:
    /**\brief Creates an event link to the given event loop.
     * \param eventLoop Event loop.
     */
    EventLink(std::shared_ptr<EventLoop> eventLoop)
    {

    }

private:

};

}
}

#endif // __AMETHYSTCORE_EVENTLINK_HPP__
