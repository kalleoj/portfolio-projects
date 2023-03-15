#include "mainwindow.hh"
#include "learningagent.hh"
#include <Eigen/Dense>

#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
{
    /*
    LearningAgent agent;
    for (int episode = 0; episode < NUM_EPISODES; episode++) {
        std::pair<int,int> state = {0, 0};
        while (state != STATE_SIZE - 1) {
            int action = agent.get_action(state);
            int next_state = state + action + rand() % 2 - 1;
            next_state = std::max(0, std::min(next_state, STATE_SIZE - 1));
            double reward = (next_state == STATE_SIZE - 1) ? 1.0 : 0.0;
            agent.update_q_value(state, action, next_state, reward);
            state = next_state;
        }
        agent.set_epsilon(agent.epsilon() * 0.99);
    }
    for (int state = 0; state < STATE_SIZE; state++) {
        int best_action = agent.get_best_action(state);
        std::cout << "State " << state << ": Best action is " << best_action << std::endl;
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
