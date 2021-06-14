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

#ifndef __AMETHYSTCORE_SYSTEM_HPP__
#define __AMETHYSTCORE_SYSTEM_HPP__

#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

#include "Events.hpp"

namespace Amethyst
{
namespace Core
{

class EventLoop;

/**@brief Base class for systems. 
 * @tparam Self Derived type.
 * @tparam Ids Event IDs this system reacts to.
 * 
 * Amethyst Systems are event-aware reactive types that perform actions within
 * their scope in response to delivered events. The reactive boilerplate is abstracted
 * away as much as possible, allowing a system to be implemented simply by deriving
 * from the appropriate instantiation of the base class and implemented the correct
 * OnEvent() methods.
 * 
 * The lifetime of a system must be greater than or equal to the lifetime of the
 * Event Loop to which it is connected.
 * 
 * The majority of the event processing boilerplate is implemented in the
 * base template. Events are delivered from the event loop via the DispatchEvent()
 * method. Effectively, a switch statement over the event IDs of interest is
 * generated once at compile time. The resulting jump table leads to a trampoline
 * which unpacks the event payload (if any) and calls the corresponding OnEvent()
 * method of the derived type.
 * 
 * All derived types must include the SYSTEM_DEFAULT_ONEVENT in public scope
 * to define the template callback method. The default implementation provides
 * runtime assertions against processing any events of interest for which an
 * OnEvent specialization has not been implemented. The derived type must implement
 * an OnEvent specialization for each event of interest.
 */
template<typename Self, EventId... Ids>
class System
{
public:
    virtual ~System() {}

    /**@brief Called when an event is delivered to the system.
     * @param ev Event.
     * @warn Only events which are specified in Ids... may be passed to this method.
     *       Passing other events may result in undefined behavior.
     */
    void DispatchEvent(const Event &ev)
    {
        // Generate (compile time) a jump table to specific dispatchers.
        // Bound the jump table by the min and max events of interest in order
        // to reduce the size of the generated code (and possibly improve
        // cache performance). The resulting jump table may be sparse but is
        // guaranteed to have defined behavior between the minimum and maximum
        // event IDs; landing on a default handler will produce a runtime error.
        using Sequence = std::make_index_sequence<maxId-minId>;
        JumpToSpecificEvent(ev, Sequence{});
    }

protected:

    System(EventLoop &eventLoop)
    {

    }

private:
    static constexpr size_t minId = std::min({static_cast<size_t>(Ids)...}); //!< Minimum event ID of interest.
    static constexpr size_t maxId = std::max({static_cast<size_t>(Ids)...}); //!< Maximum event ID of interest.

    /**@brief Uses a generated jump table to call the correct specific dispatcher.
     * @tparam Indices Indices of the jump table starting at zero.
     * @param ev Event.
     */
    template<size_t... Indices>
    inline void JumpToSpecificEvent(const Event &ev, std::index_sequence<Indices...>)
    {
        // Generate jump table.
        using OwnType = std::remove_pointer_t<decltype(this)>;
        using Fn = void (OwnType::*)(const Event&);
        static constexpr Fn jmpTable[] = {
            &OwnType::template DispatchSpecificEvent<static_cast<EventId>(minId + Indices)>...
        };

        // Invoke specific dispatcher.
        auto index = static_cast<size_t>(ev.eventId) - minId;
        std::invoke(jmpTable[index], this, ev);
    }

    /**@brief Inner dispatcher that unpacks an event and calls the final callback.
     * @tparam InnerId Received event ID.
     * @param ev Event.
     */
    template<EventId InnerId>
    inline void DispatchSpecificEvent(const Event &ev)
    {
        assert(ev.eventId == InnerId);
        
        // Dispatch according to payload type, if any.
        using Info = EventInfo<InnerId>;
        if constexpr (std::is_void<typename Info::PayloadType>::value)
        {
            static_cast<Self*>(this)->template OnEvent<InnerId>();
        }
        else
        {
            const auto* payload = static_cast<const Info::PayloadType*>(ev.data);
            static_cast<Self*>(this)->template OnEvent<InnerId>(payload);
        }
    }
    
};

/**@brief Defines default event handlers with error logging. */
#define SYSTEM_DEFAULT_ONEVENT \
    template<EventId Id> \
    void OnEvent() \
    { \
        assert(false); \
    } \
    template<EventId Id> \
    void OnEvent(const typename EventInfo<Id>::PayloadType*) \
    { \
        OnEvent<Id>(); \
    } \

}
}

#endif
