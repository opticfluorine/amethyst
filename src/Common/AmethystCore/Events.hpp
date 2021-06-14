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

#ifndef __AMETHYSTCORE_EVENTS_HPP__
#define __AMETHYSTCORE_EVENTS_HPP__

#include <cstddef>

namespace Amethyst {
namespace Core {

    /**@brief Enumeration of supported event IDs.
     */
    enum struct EventId
    {
        // === Core Events ===
        CORE_SHUTDOWN, //!< Engine shutdown event.

        // === Internal Bookkeeping ===
        _MAX_EVENT     //!< Maximum event ID value. Not an actual event.
    };

    /**@brief Maximum event size, in bytes.
     * Chosen such that the full event size is a power of two and the
     * events fit cleanly into memory pages (no fragmentation within
     * a memory pool of events).
     */
    constexpr size_t MAX_EVENT_SIZE = 128 - sizeof(EventId) - sizeof(size_t);

    /**@brief General purpose event data structure.
     * The general event structure encodes the payload struct as a byte
     * array having fixed length for a given event ID.
     */
    struct Event
    {
        EventId eventId; //!< Event ID.
        size_t refCount; //!< Reference count controlled from the event loop.
        char data[MAX_EVENT_SIZE]; //!< Data payload byte array.
    };

    /**@brief Encodes type information for the given event.
     * @tparam Id Event ID.
     */
    template<EventId Id>
    struct EventInfo { };

}
}

#endif
