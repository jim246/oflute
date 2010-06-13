#include <gstreamermm.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    Glib::RefPtr<Gst::Pipeline> pipeline;
    Glib::RefPtr<Gst::Element> element_source, element_filter, element_sink;

    // Initialize Gstreamermm:
    Gst::init_check();

    // Create pipeline:
    pipeline = Gst::Pipeline::create("my-pipeline");

    // Create elements:
    element_source = Gst::ElementFactory::create_element("fakesrc");
    element_filter = Gst::ElementFactory::create_element("identity");
    element_sink = Gst::ElementFactory::create_element("fakesink");

    // We must add the elements to the pipeline before linking them:
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
#endif
	pipeline->add(element_source)->add(element_filter)->add(element_sink);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch (std::runtime_error& ex)
    {
	std::cerr << "Exception while adding: " << ex.what() << std::endl;
	return 1;
    }
#endif

    // Link the elements together:
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
#endif
	element_source->link(element_filter)->link(element_sink);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    }
    catch(const std::runtime_error& error)
    {
	std::cerr << "Exception while linking: " << error.what() << std::endl;
    }
#endif
    return 0;
}
