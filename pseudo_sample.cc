#include "pipe_inc.h"

void callback(int msg_type)
{
    // some stuffs
}

int main(void)
{
    // single process case
    Pipeline pipe;
    pipe.add(TYPE::INPUT, new input_filter())
        .add(TYPE::PROCESSING, new process_filter())
        .add(TYPE::OUTPUT, new output_filter());
    pipe.run();

    // multi process case(local)
    Filter proc_filter;
    proc_filter.add_inputs(local::named_pipe, "/tmp/comm1");
    proc_filter.add_output(local::named_pipe, "/tmp/comm2");
    pipe.add(TYPE::PROCESSING, proc_filter);
    pipe.run();

    // multi process case(remote)
    Filter proc_filter2;
    proc_filter2.add_inputs(local::tcp, "ip or domain", port1);
    proc_filter2.add_output(local::tcp, "ip or domain", port2);
    pipe.add(TYPE::PROCESSING, proc_filter2);
    pipe.run();

    return 0;
}
