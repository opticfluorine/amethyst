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

#ifndef __AMETHYSTCORE_EVENTPOOL_HPP__
#define __AMETHYSTCORE_EVENTPOOL_HPP__

#include <boost/pool/object_pool.hpp>

#include "Events.hpp"

namespace Amethyst {
namespace Core {

    /**@brief Provides a memory pool for reusable events.
     */
    class EventPool final
    {
    public:
        EventPool();
        ~EventPool() = default;

        EventPool(const EventPool&) = delete;
        EventPool& operator=(const EventPool&) = delete;

        constexpr static size_t POOL_SIZE = 1024; //!< Pool size in events.

        Event *BorrowEvent();
        void ReturnEvent(Event *ev);

    private:
        boost::object_pool<Event> pool; //!< Memory pool.

    };

}
}

#endif
