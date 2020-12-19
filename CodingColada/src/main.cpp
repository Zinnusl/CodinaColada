// CodingColada.cpp : Defines the entry point for the application.
//

#include "App.h"
#include "opengl/OpenGLRenderer.h"
#include "opengl/OpenGLInput.h"

//namespace di = boost::di;
using std::cout;
using std::endl;

//class injected_and_bound : public di::config {
//public:
//	static auto policies(...) noexcept {
//		using namespace di::policies;
//		using namespace di::policies::operators;
//		return di::make_policies(
//			constructible(is_bound<di::_>{})
//		);
//	}
//};

//SDL demands this signature for main()
int main(int argc, char* args[])
{
	/*auto injector = di::make_injector<injected_and_bound>(		
		di::bind<std::ostream>.to(std::cerr),
		di::bind<std::istream>.to(std::cin),
		di::bind<ArgsParserInputOutput>.to(parser),
		di::bind<IJackOptionSetter::videomode_t>.to(videomode_options[args["mode"].as<std::string>()])[di::override],
		di::bind<IJackOptionSetter>.to<JackOptionSetter>(),

		di::bind<IInput::ifactory_t>.to([is_input_dvs](auto const& injector, auto const& dependency) -> IInput::ifactory_t& {
			if (is_input_dvs) {
				return *InputDVS::factory_t{}(injector, dependency);
			}
			else {
				return *InputColorBars::factory_t{}(injector, dependency);
			}
			}),

		di::bind<IOutput::ifactory_t>.to(OutputDVS::factory_t{}),
				di::bind<IStream::ifactory_t>.to(Stream::factory_t{}),
				di::bind<ICardHandle::ifactory_t>.to(CardHandle::factory_t{})
				);
				*/
	/*
	auto injector = di::make_injector(
	//auto injector = di::make_injector<injected_and_bound>(
		di::bind<std::ostream>.to(std::cerr),
		di::bind<std::istream>.to(std::cin),
		di::bind<IRenderer>.to<OpenGLRenderer>(),
		di::bind<IInput>.to<OpenGLInput>(),
		di::bind<Engine>.in(di::singleton).to<Engine>(),
		di::bind<boost::di::extension::ifactory<GameManager>>.to(boost::di::extension::factory<GameManager>{})
	);
	*/
	std::unique_ptr<IRenderer> renderer = std::make_unique<OpenGLRenderer>();
	std::unique_ptr<IInput> input = std::make_unique<OpenGLInput>();

	std::unique_ptr<Engine> engine = std::make_unique<Engine>(std::move(renderer), std::move(input));
	auto app = std::make_unique<App>(std::cout, std::move(engine));
	app->run();
	
	return 0;
}
