#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WServer.h>
#include <Wt/WText.h>

class HelloApplication : public Wt::WApplication {
public:
    HelloApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env)
    {
        // Set the application title
        setTitle("Blappy Web Server");

        // Create a container widget and add it to the root
        auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());

        // Add a text widget to the container
        container->addWidget(std::make_unique<Wt::WText>(
            "Welcome to the Blappy Web Server! This is a simple Wt web application."));
    }
};

int main(int argc, char** argv)
{
    try {
        // Start the Wt server and create an instance of the application
        return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
            return std::make_unique<HelloApplication>(env);
        });
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}