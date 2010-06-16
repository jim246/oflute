#include <gstreamermm.h>
#include <iostream>
using namespace std;


bool on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */, 
		    const Glib::RefPtr<Gst::Message>& message)
{
    if(message -> get_message_type() == Gst::MESSAGE_ELEMENT){
	//std::cout << "debug: on_bus_message: unhandled message=" << G_OBJECT_TYPE_NAME(message->gobj()) << std::endl;
	Gst::Structure estructura = message -> get_structure();
	cout << estructura . get_name() << endl; // == "spectrum"

	const gfloat *magnitudes;
	const GValue *phases;
	const GValue *mag, *phase;

      	gdouble freq;
	guint i;

	GType p = estructura . get_field_type("magnitudes");
	cout << p << endl;
//	estructura . get_field("magnitude", magnitudes);

/*
	magnitudes = gst_structure_get_value (s, "magnitude");
	phases = gst_structure_get_value (s, "phase");
	
	for (i = 0; i < spect_bands; ++i) {
	    freq = (gdouble) ((AUDIOFREQ / 2) * i + AUDIOFREQ / 4) / spect_bands;
	    mag = gst_value_list_get_value (magnitudes, i);
	    phase = gst_value_list_get_value (phases, i);
	    
	    if (mag != NULL && phase != NULL) {
		g_print ("band %d (freq %g): magnitude %f dB phase %f\n", i, freq,
			 g_value_get_float (mag), g_value_get_float (phase));
	    }
	}
	g_print ("\n"); //*/
    


}
        
    return true;
}


Glib::RefPtr<Glib::MainLoop> mainloop;
int main(int argc, char** argv)
{
    Glib::RefPtr<Gst::Pipeline> pipeline;
    Glib::RefPtr<Gst::Element> element_source, element_filter, element_sink;

    // Initialize Gstreamermm:
    Gst::init_check();

    // Create pipeline:
    pipeline = Gst::Pipeline::create("my-pipeline");

    // Create elements:
    element_source = Gst::ElementFactory::create_element("pulsesrc");
    element_filter = Gst::ElementFactory::create_element("spectrum");
    element_sink = Gst::ElementFactory::create_element("pulsesink");

    element_filter -> set_property("post-messages", true);
    element_filter -> set_property("interval", 500000000);

    Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
    bus->add_watch( sigc::ptr_fun(&on_bus_message) );

    // We must add the elements to the pipeline before linking them:

    try
    {
	pipeline->add(element_source)->add(element_filter)->add(element_sink);
    }
    catch (std::runtime_error& ex)
    {
	std::cerr << "Exception while adding: " << ex.what() << std::endl;
	return 1;
    }

    // Link the elements together:
    try
    {

	element_source->link(element_filter)->link(element_sink);
    }
    catch(const std::runtime_error& error)
    {
	std::cerr << "Exception while linking: " << error.what() << std::endl;
    }


    // Now set the whole pipeline to playing and start the main loop:
    std::cout << "Setting pipeline to PLAYING." << std::endl;
    pipeline->set_state(Gst::STATE_PLAYING);
    std::cout << "Pipeline is playing." << std::endl;
    mainloop = Glib::MainLoop::create();
    mainloop->run();
    
    // Clean up nicely:
    std::cout << "Returned. Stopping pipeline." << std::endl;
    pipeline->set_state(Gst::STATE_NULL);
    return 0;
}
