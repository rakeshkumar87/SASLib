#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include "applicationui.hpp"

#include <Qt/qdeclarativedebug.h>
#include "SAService.hpp"
#include <QFutureWatcher>
#include "Message.hpp"

using namespace bb::cascades;

void run_LoginTest() {
    mail::sas::AccountSettings account("rakeshtest14@gmail.com", "test*1234!", "imap.gmail.com", 993);
    mail::sas::SAService service(account);
    Q_ASSERT(service.login());
}

void run_FoldersTest() {
    mail::sas::AccountSettings account("rakeshtest14@gmail.com", "test*1234!", "imap.gmail.com", 993);
    mail::sas::SAService service(account);
    Q_ASSERT(service.login());

    mail::sas::FolderList list = service.folders("", "*");
    Q_ASSERT( ( list.size() > 0 ) );
}

void run_MessagesTest() {
    mail::sas::AccountSettings account("rakeshtest14@gmail.com", "test*1234!", "imap.gmail.com", 993);
    mail::sas::SAService service(account);
    Q_ASSERT(service.login());

    mail::sas::MessageList list = service.messages("INBOX", "1:*");
    Q_ASSERT( ( list.size() > 0) );
}

void run_AsyncMessagesTest() {
    mail::sas::AccountSettings account("rakeshtest14@gmail.com", "test*1234!", "imap.gmail.com", 993);
    mail::sas::SAService service(account);
    Q_ASSERT(service.login());

    QFutureWatcher<mail::sas::MessageList> watcher;
    service.asyncMessages("INBOX", "1:*", watcher);
    mail::sas::MessageList list = watcher.future().result();
    Q_ASSERT( (list.size() > 0) );
}


Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);

    run_LoginTest();
    run_FoldersTest();
    run_MessagesTest();
    run_AsyncMessagesTest();

    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    new ApplicationUI(&app);

    // Enter the application main event loop.
    return Application::exec();
}
