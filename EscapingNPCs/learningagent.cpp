#include "learningagent.hh"
#include <iostream>
#include <vector>
#include <random>




LearningAgent::LearningAgent() {
    q_values_ = std::vector<std::vector<double>>(STATE_SIZE, std::vector<double>(ACTION_SIZE, 0.0));
    rand_dist_ = std::uniform_real_distribution<>(0.0, 1.0);
}

int LearningAgent::get_action(int state) {
    double rand_num = rand_dist_(generator_);
    if (rand_num < epsilon_) {
        return generator_() % ACTION_SIZE;
    }
    else {
        return get_best_action(state);
    }
}

int LearningAgent::get_best_action(int state) {
    int best_action = 0;
    double best_value = q_values_[state][0];
    for (int i = 1; i < ACTION_SIZE; i++) {
        if (q_values_[state][i] > best_value) {
            best_value = q_values_[state][i];
            best_action = i;
        }
    }
    return best_action;
}

void LearningAgent::update_q_value(int state, int action, int next_state, double reward) {
    double old_value = q_values_[state][action];
    double max_next_value = get_max_q_value(next_state);
    double new_value = old_value + ALPHA * (reward + GAMMA * max_next_value - old_value);
    q_values_[state][action] = new_value;
}

double LearningAgent::get_max_q_value(int state) {
    double max_value = q_values_[state][0];
    for (int i = 1; i < ACTION_SIZE; i++) {
        if (q_values_[state][i] > max_value) {
            max_value = q_values_[state][i];
        }
    }
    return max_value;
}

void LearningAgent::set_epsilon(double epsilon) {
    epsilon_ = epsilon;
}
