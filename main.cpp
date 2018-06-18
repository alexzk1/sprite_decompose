#include "application.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    app.setApplicationName("Sprite Decomposer");
    app.setApplicationVersion("0.6");
    app.setApplicationDisplayName("Sprite Decomposer");
    app.setOrganizationDomain("pasteover.net");
    app.setOrganizationName("pasteover.net");

    Q_INIT_RESOURCE(lang);
    app.loadTranslations(":/lang");

    Interface w;
    w.show();

    return app.exec();
}
