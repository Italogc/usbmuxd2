//
//  TCP.hpp
//  usbmuxd2
//
//  Created by tihmstar on 30.05.21.
//

#ifndef TCP_hpp
#define TCP_hpp

#include <stdint.h>
#include <memory>
#include "Devices/USBDevice.hpp"
#include "Manager/USBDeviceManager.hpp"
#include <libgeneral/Manager.hpp>
#include <mutex>
#include <poll.h>


class Client;
class TCP : public tihmstar::Manager {
    enum mux_conn_state {
        CONN_CONNECTING,    // SYN
        CONN_CONNECTED,        // SYN/SYNACK/ACK -> active
        CONN_REFUSED,        // RST received during SYN
        CONN_DYING            // RST received
    } _connState;
    struct TCPSenderState {
        uint32_t seq, seqAcked, ack, acked, inWin, win;//(TCP::bufsize >> 8)
    } _stx;
    
    uint16_t _sPort;
    uint16_t _dPort;
    std::shared_ptr<USBDevice> _dev;
    std::shared_ptr<Client> _cli;
    std::mutex _lockStx;
    tihmstar::Event _lockCanSend; //puts threads to sleep if we can't send data

    char *_payloadBuf;
    struct pollfd _pfd;

    void loopEvent() override;
    void stopAction() noexcept override;
    void send_tcp(uint8_t flags);
    void send_ack();
    size_t send_data(void *buf, size_t len);

public:
    static constexpr int bufsize = 0x80000;
    static constexpr int TCP_MTU = (USB_MTU-sizeof(tcphdr)-sizeof(USBDevice::mux_header))&0xff00;

    TCP(uint16_t sPort, uint16_t dPort, std::shared_ptr<USBDevice> dev, std::shared_ptr<Client> cli);
    ~TCP();

    void kill() noexcept;
    void handle_input(tcphdr* tcp_header, uint8_t* payload, uint32_t payload_len);
    void connect();

    static void send_RST(USBDevice *dev, tcphdr *hdr);
};

#endif /* TCP_hpp */
