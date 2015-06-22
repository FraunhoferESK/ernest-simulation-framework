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
#ifndef ERNEST_MULTILEVEL_QUEUE_HEADER
#define ERNEST_MULTILEVEL_QUEUE_HEADER

#include <vector>
#include <list>
#include <ernest/task.hpp>

namespace ERNEST {
using namespace std;


/**
 * Class implenting a multi-lvel queue.
 */
class MultiLevelQueue
{
public:
    /**
     * Constructor for MultiLevelQueue.
     *
     * @param maxPriority is type integer
     */
    MultiLevelQueue(int maxPriority);

    /**
     * AddTask function.
     *
     * @param t Pointer to Task
     */
    void AddTask(Task* t);

    /**
     * RemoveTask function.
     *
     * @param t Pointer to Task
     */
    void RemoveTask(Task* t);

    /**
     * GetTaskToRun function.
     *
     * @return Queue
     */
    Task* GetTaskToRun();

private:
    MultiLevelQueue(const MultiLevelQueue&);
    MultiLevelQueue& operator=(const MultiLevelQueue&);

    /**
     * A vector with inner lists, that serve as readyQueue
     * for each priority level.
     */
    std::vector< std::list<Task*> > readyQueues;
};

} // namespace ERNEST

#endif /* ERNEST_MULTILEVEL_QUEUE_HEADER */
