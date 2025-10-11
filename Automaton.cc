#include "Automaton.h"
#include <iostream>
using namespace std;


namespace fa {

    Automaton::Automaton() {
    }

  bool Automaton::isValid() const {
    if (alphabet.empty()) return false;
    if (states.empty()) return false;
    return true;
  };

  bool Automaton::addSymbol(char symbol) {
    if (!isgraph(symbol) || symbol == fa::Epsilon) return false;
    alphabet.push_back(symbol);
    return true;
  }

  bool Automaton::removeSymbol(char symbol) {
    if (!hasSymbol(symbol)) return false;
    alphabet.erase(std::find(alphabet.begin(), alphabet.end(), symbol));
    return true;
  }

  bool Automaton::hasSymbol(char symbol) const {
    auto sym = std::find(alphabet.begin(), alphabet.end(), symbol);
    return sym != alphabet.end();
  }

  std::size_t Automaton::countSymbols() const {
    return alphabet.size();
  }

  bool Automaton::addState(int state) {
    if (hasState(state)) return false;
    states.push_back(state);
    return true;
  }

  bool Automaton::removeState(int state) {
    if (!hasState(state)) return false;
    states.erase(std::find(states.begin(), states.end(), state));
    return true;
  }

  bool Automaton::hasState(int state) const {
    auto sta = std::find(states.begin(), states.end(), state);
    return sta != states.end();
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {
    if (!hasState(state)) return;
    if (isStateInitial(state)) return;
    initial.push_back(state);
  }

  bool Automaton::isStateInitial(int state) const {
    auto sta = std::find(initial.begin(), initial.end(), state);
    return sta != initial.end();
  }

  void Automaton::setStateFinal(int state) {
    if (!hasState(state)) return;
    if (isStateFinal(state)) return;
    final.push_back(state);
  }

  bool Automaton::isStateFinal(int state) const {
    auto sta = std::find(final.begin(), final.end(), state);
    return sta != final.end();
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to)) return false;
    transitions[from][alpha].push_back(to);
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasTransition(from, alpha, to)) return false;
    auto &trans = transitions[from][alpha];
    trans.erase(std::find(trans.begin(), trans.end(), to));
    return true;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    if (transitions.find(from) == transitions.end()) return false;
    auto &transChar = transitions.at(from);
    if (transChar.find(alpha) == transChar.end()) return false;
    auto &transInt = transitions.at(from).at(alpha);
    if (std::find(transInt.begin(), transInt.end(), to) == transInt.end()) return false;
    return true;
  }

  std::size_t Automaton::countTransitions() const{
    std::size_t total = 0;
    for (auto &pairFrom : transitions) {
        for (auto &pairAlpha : pairFrom.second) {
            total += pairAlpha.second.size();
        }
    }
    return total;
  }

  void Automaton::prettyPrint(std::ostream& os) const {
    os << "Initial states :" << std::endl;
    os << "    ";
    for (auto state : initial)
      os << state << " ";
    os << endl;

    os << "Final States :" << std::endl;
    os << "    ";
    for (auto state : final)
      os << state << " ";
    os << endl;

    os << "Transitions :" << std::endl;
    os << "    ";
    for (auto from : transitions) {
      os << "For state " << from.first << " : " << std::endl;
      for (auto alpha : from.second) {
        os << "        For letter" << alpha.first << " :";
        for (auto to : alpha.second)
          os << " " << to;
      }
      os << std::endl;
    }
  }

  bool Automaton::hasEpsilonTransition() const {
    if (!hasSymbol(fa::Epsilon)) return false;
    for (auto state : transitions) {
      auto &sta = state.second;
      if (sta.find(fa::Epsilon) == sta.end())
        return false;
    }
    return true;
  }

  bool Automaton::isDeterministic() const {
    for (auto state : transitions) {
      for (auto alpha : state.second) {
        auto &to = alpha.second;
        if (to.size() > 1) return false;
        if (std::find(to.begin(), to.end(), fa::Epsilon) != to.end()) return false;
      }
    }
    return true;
  }



  bool Automaton::isComplete() const {
    for (auto state : transitions) {
      if (state.second.size() != alphabet.size()) return false;
    }
    return true;
  }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    if (automaton.isComplete()) return automaton;
    Automaton comp = automaton;
    int newState = -1;
    comp.addState(newState);
    for (auto from : comp.transitions) {
      for (auto symbol : comp.alphabet) {
        if (from.second.find(symbol) == from.second.end()) {
          comp.addTransition(from.first, symbol, newState);
        }
      }
    }
    return comp;
  }

  Automaton Automaton::createComplement(const Automaton& automaton) {
    return automaton;
  }

  Automaton Automaton::createMirror(const Automaton& automaton) {
    Automaton mirror = automaton;
    mirror.initial = automaton.final;
    mirror.final = automaton.initial;
    for (auto from : automaton.transitions) {
      for (auto alpha : from.second) {
        for (auto to : alpha.second) {
          mirror.addTransition(to, alpha.first, from.first);
        }
      }
    }
    return mirror;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> result;
    for (auto from : origin) {
      for (auto to : states) {
        if (hasTransition(from, alpha, to)) 
          result.insert(to);
      }
    }
    return result;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    std::set<int> path(initial.begin(), initial.end());
    for (auto c : word) {
        path = makeTransition(path, c);
    }
    return path;
  }

  bool Automaton::match(const std::string& word) const {
    std::set<int> match = readString(word);
    bool stateInitial = false;
    bool stateFinal = false;
    for (auto state : match) {
      if (isStateInitial(state)) stateInitial = true;
      if (isStateFinal(state)) stateFinal = true;
    }
    if (!stateInitial || !stateFinal) return false;
    return true;
  }
}

