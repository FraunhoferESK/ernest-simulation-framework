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
#ifndef ERNEST_RUNTIME_ENVIRONMENT_HEADER
#define ERNEST_RUNTIME_ENVIRONMENT_HEADER

#include <vector>
#include "ecu.hpp"
#include "software_function.hpp"
#include "communication_manager.hpp"
#include "ernest_addition.hpp"

namespace ERNEST
{
struct Alarm;
class SoftwareFunction;
class OsekOS;

/**
 * Enumeration created for the different kinds of notifications
 */
enum NotificationKind {
    NONE,
    TASK,
};


class GenericObjectBuffer
{
public:

	virtual ~GenericObjectBuffer() {}

    virtual void SetData(void* data) = 0;

    /**
     * Function setting the task context.
     *
     * @param: context the TaskContext pointer.
     */
    void setTaskContext(TaskContext* context)
    {
        m_context = context;
    }

    /**
     * Function setting the task context.
     *
     * @return: TaskContext pointer.
     */
    TaskContext* getTaskContext()
    {
        return m_context;
    }

private:
    TaskContext* m_context;
};


template<class MessageType>
class MessageObjectBuffer : public GenericObjectBuffer
{
public:
    Communication m_dest;
    MessageType m_data;
    bool m_new_data;
    SignalId m_signal_id;
    NotificationKind m_notification_kind;

    /**
     * Default constructor
     */
    MessageObjectBuffer() :
    	m_dest(Local),
		m_new_data(false),
		m_signal_id(0),
		m_notification_kind(NONE)
    {
    }

    /**
     * Function to set the data of the MessageObjectBuffer.
     *
     * @param data is a pointer to the location of the data
     */
    virtual void SetData(void* data)
    {
        MessageType *message = (MessageType*) data;
        m_data = *message;
    }

private:
    /**
     * Disable copy constructor
     */
    MessageObjectBuffer(const MessageObjectBuffer&);

    /**
     * Disable copy assignment operator
     */
    MessageObjectBuffer& operator=(const MessageObjectBuffer&);
};


class RuntimeEnvironment
{
public:
    /**
     * Constructor for RuntimeEnvironment.
     *
     * @param os is an OsekOS pointer
     */
    RuntimeEnvironment(OsekOS* os);

    /**
     * Function for sending data.
     *
     * @param signal_id represents the id of the corresponding Signal
     * @param data of TransmitType which will be send
     */
    template <class TransmitType>
    void SendSignal(SignalId signal_id, TransmitType &data)
    {
        MessageObjectBuffer<TransmitType> *buffer =
            static_cast<MessageObjectBuffer<TransmitType>* >(m_signal_buffer[signal_id]);

        if (buffer != nullptr) {
            buffer->m_data = data;
        }

        if (m_local_out_routing_table[signal_id] != Local) {
            m_os->GetCommunicationManager()->TransmitOverBus(signal_id,
                                  data,
                                  m_local_out_routing_table[signal_id]);
        }
    }

    /**
     * Function to receive the raw signal data.
     *
     * If buffer is nullptr, we just received a signal which was broadcasted
     * and is not suitable for us.
     *
     * @param signalId represents the id of the corresponding Signal.
     * @param data is a pointer to the location in memory to store the received data
     * @param length represents the data length.
     */
    void ReceiveSignalRaw(SignalId signal_id, void* data, size_t length);


    /**
     * Function to receive data.
     *
     * @param signal_id represents the id of the corresponding Signal
     * @param data of TransmitType which have been received
     */
    template <class TransmitType>
    void ReadSignal(SignalId signal_id, TransmitType& data)
    {
        MessageObjectBuffer<TransmitType> *buffer =
            static_cast<MessageObjectBuffer<TransmitType>* >(m_signal_buffer[signal_id]);
        assert(buffer != nullptr);
        data = buffer->m_data;
    }

    /**
     * Function to add an entry into the routing table of the
     * RuntimeEvnironment.
     *
     * @param signal_id represents the id of the corresponding Signal
     * @param dest is the Communication over which the signal is going
     *             to be transmitted
     * @param context is a TaskContect pointer
     */
    template <class TransmitType>
    void AddRoutingEntry(SignalId signal_id,
                         Communication dest,
                         TaskContext *context)
    {
        MessageObjectBuffer<TransmitType> *mbo =
            new MessageObjectBuffer<TransmitType>();
        mbo->setTaskContext(context);
        m_local_out_routing_table[signal_id] = dest;
        m_signal_buffer[signal_id] = static_cast<GenericObjectBuffer*>(mbo);
    }

private:
    OsekOS* m_os;
    std::vector<SoftwareFunction*> m_software_function_list;
    map<SignalId, Communication> m_local_out_routing_table;
    map<SignalId, Communication> m_local_in_routing_table;
    map<SignalId, GenericObjectBuffer*> m_signal_buffer;
};

} // namespace ERNEST

#endif /* ERNEST_RUNTIME_ENVIRONMENT_HEADER */
