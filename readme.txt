
SAService is a utility service to fetch email data from the mail servers. Though this supports only IMAP now, the API itself is protocol agnostic and can easily extend to support 
other protocols such as pop, activesync and syncml. 

Core Components:

SAService: API for clients to fetch messages and folders. Clients need to pass in account settings
           containing mail server configuration and user authorization parameters.

StateMachineExecutor: Its the core component on which the design is based on. This executes a network based 
                      state machine insuring the typical state transitions of Request, Network Send, Network Read, Response occur.


INetworkSingleState: Definition of a state in the state machine.

CommunicationService: Performs socket connection management, allows sending and receiving of data.


IMAP Specific Components:

IMAPLogin: Contains network states for IMAP Login command.
IMAPList: Contains network states for IMAP LIST command. Used for retrieving folders.
IMAPSelect: Contains network states for IMAP SELECT command. Used to select a folder for read access.
IMAPFetch: Contains network states for IMAP Fetch command. Used to fetch messages for the selected folder.
IMAPLogout: Contains network states for IMAP Logout command.



 