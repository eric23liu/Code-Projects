/* 
*  Simple packet capture and analysis program
*  Identifies IP and ARP
*  Uses libpcap library (required to compile)
*
*  To compile, execute in terminal:
*      gcc pcap.cpp -lpcap -o pcap
*
*  To run, execute:
*      ./pcap
*
*  Terminate by pressing ctrl-c
*
*  To Mike and Brandon:
*      Try porting to Windows (the libpcap equivalent for Windows is wincap)
*      This should give you some practice coding in C++
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>  
#include <netinet/ip.h>

void packet_handler(u_char *args, const struct pcap_pkthdr* h, const u_char* p) {

    struct ip* pkt_ptr = (struct ip*) p;
    struct pcap_pkthdr header = *h;
    struct ether_header* eth_ptr = (struct ether_header*) p;

    printf( " @ %s",ctime((const time_t*)&header.ts.tv_sec) );    
    printf( "   ETH SRC: %s\n", ether_ntoa( (struct ether_addr*) eth_ptr->ether_shost) );
    printf( "   ETH DST: %s\n", ether_ntoa( (struct ether_addr*) eth_ptr->ether_dhost) );
    
    if ( ntohs(eth_ptr->ether_type) == ETHERTYPE_IP) {
        printf( "   IP:\n");
        printf( "     IP SRC: %s\n",   inet_ntoa(pkt_ptr->ip_src) );
        printf( "     IP DST: %s\n\n", inet_ntoa(pkt_ptr->ip_dst) );
        
    } else if ( ntohs(eth_ptr->ether_type) == ETHERTYPE_ARP){
        printf( "   ARP:\n");
        printf( "     IP SRC: %s\n",   inet_ntoa(pkt_ptr->ip_src) );
        printf( "     IP DST: %s\n\n", inet_ntoa(pkt_ptr->ip_dst) );
        
    } else {
        printf( "   Type Unsupported\n\n" );
        
    }
    
}

int main ( int argc, char **argv ) {
    
    int promiscuous_mode = 0;
    
    if (argc > 1){
        if (argv[1] == "all") {
            promiscuous_mode = 1;
        } else if (argv[1] == "help") {
            printf("HELP SECTION GOES HERE\n");
        }
    }
    
    char* dev_ptr;
    char err[PCAP_ERRBUF_SIZE];
    
    struct in_addr net;
    struct in_addr mask;
    struct ether_header* ether_header;
    
    pcap_t* descr_ptr;
    
    dev_ptr = pcap_lookupdev(err);
    pcap_lookupnet(dev_ptr, &net.s_addr, &mask.s_addr, err);
    
    printf("\n Analyzing %s\n", dev_ptr);
    printf(" NET : %s\n", inet_ntoa(net) );
    printf(" MASK: %s\n\n", inet_ntoa(mask) );   
    
    descr_ptr = pcap_open_live(dev_ptr, BUFSIZ, promiscuous_mode, -1, err);
    
    pcap_loop(descr_ptr, -1, packet_handler, NULL);
    
    return 0;
}
