Server Access Service

SAService is a utility service to fetch email data from the mail servers. Though this supports only IMAP for now, 
the API itself is protocol agnostic and can easily extend to support other protocols such as pop, activesync and syncml. 

Core Components:

SAService: API for clients to fetch Email messages and Account folders from the mail server. Clients would need to pass 
           in account settings containing mail server configuration and user authorization parameters. It provides both
           synchronous and asynchronous versions such that clients do not have to be blocked for the request to be 
           completed.

StateMachineExecutor: The core component on which the design is based on. This executes a network based
                      state machine insuring the typical state transitions of Request, Network Send, 
                      Network Read, Response occur.
                      
                      Typically the flow for a request is four steps:
                      1) Construct a Request into a byte array.
                      2) Send the request to the server.
                      3) Receive the response.
                      4) Parse the response and decide what to do next.
                      
                      Though the normal flow is an exact transition between the above states, the flow
                      could be interrupted due to
                      
                      1) Network errors
                      2) Parsing errors
                      3) Other possible recoverable errors
                      
                      StateMachineExecutor allows easily handling these cases. Each state could decide on what
                      next to do to recover.
                      

INetworkSingleState: Definition of a state in the state machine.

CommunicationService: Performs socket connection management, allows sending and receiving of data.

IMAP Specific Components:

IMAPLogin: Contains network states for IMAP Login command.
IMAPList: Contains network states for IMAP LIST command. Used for retrieving folders.
IMAPSelect: Contains network states for IMAP SELECT command. Used to select a folder for read access.
IMAPFetch: Contains network states for IMAP Fetch command. Used to fetch messages for the selected folder.
IMAPLogout: Contains network states for IMAP Logout command.



 
