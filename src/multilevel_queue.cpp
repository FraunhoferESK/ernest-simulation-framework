/* Copyright (C) 2014 Fraunhofer Institute for Embedded Systems and
 * Communication Technologies ESK
 *
 * This file is part of ERNEST.
 * 
 * ERNEST is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ERNEST is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ERNEST.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ernest/ernest_addition.hpp"
#include "ernest/multilevel_queue.hpp"

namespace ERNEST
{

MultiLevelQueue::MultiLevelQueue(int maxPriority)
{
    // Allocate the memory required for storing at least
    // (highestPriority + 1) lists (one for each priority level)
    readyQueues.reserve(maxPriority + 1);

    // Add the (highestPriority + 1) lists
    for(int i = 0; i <= maxPriority; i++) {
        std::list<Task*> list;
        readyQueues.push_back(list);
    }
}

void MultiLevelQueue::AddTask(Task* t)
{
    readyQueues.at(t->GetPriority()).push_back(t);
}

void MultiLevelQueue::RemoveTask(Task* t)
{
    readyQueues.at(t->GetPriority()).remove(t);
}

Task* MultiLevelQueue::GetTaskToRun()
{
    // Go through the readyQueues backwards (highest priorities first)
    for(int i = readyQueues.size() - 1; i >= 0; i--) {
        if(readyQueues.at(i).size() > 0) {
            return readyQueues.at(i).front();
        }
    }
    return nullptr;
}

} // namespace ERNEST
