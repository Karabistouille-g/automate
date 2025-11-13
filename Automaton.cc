#include "Automaton.h"
#include <iostream>
#include <vector>
using namespace std;


namespace fa {

    Automaton::Automaton() {
    }

  bool Automaton::isValid() const {
    if (alphabet.empty()) return false;
    if (states.empty()) return false;
    return true;
  }

  bool Automaton::addSymbol(char symbol) {
    if (!isgraph(symbol)) return false;
    if (hasSymbol(symbol)) return false;
    alphabet.insert(symbol);
    return true;
  }

  bool Automaton::removeSymbol(char symbol) {
    if (!hasSymbol(symbol)) return false;
    std::vector<std::tuple<int, char, int>> remove;
    for (auto current : transitions) {
      if (std::get<1>(current) == symbol) {
        remove.push_back(current);
      }
    }
    for (auto rm : remove) {
      removeTransition(std::get<0>(rm), std::get<1>(rm), std::get<2>(rm));
    }
    alphabet.erase(symbol);
    return true;
  }

  bool Automaton::hasSymbol(char symbol) const {
    return alphabet.count(symbol) == 1;
  }

  std::size_t Automaton::countSymbols() const {
    return alphabet.size();
  }

  bool Automaton::addState(int state) {
    if (state < 0) return false;
    if (hasState(state)) return false;
    states.insert({state, NONE});
    return true;
  }

  bool Automaton::removeState(int state) {
    if (!hasState(state)) return false;
    std::vector<std::tuple<int, char, int>> remove;
    for (auto current : transitions) {
      if (std::get<0>(current) == state || std::get<2>(current) == state) {
        remove.push_back(current);
      }
    }
    for (auto rm : remove) {
      removeTransition(std::get<0>(rm), std::get<1>(rm), std::get<2>(rm));
    }
    states.erase(state);
    return true;
  }

  bool Automaton::hasState(int state) const {
    return states.count(state) == 1;
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {
    if (!hasState(state)) return;
    if (isStateInitial(state)) return;
    if (isStateFinal(state)) {
      states[state] = BOTH;
      return;
    }
    states[state] = INITIAL;
  }

  bool Automaton::isStateInitial(int state) const {
    if (states.count(state) == 0) return false;
    return states.at(state) == INITIAL || states.at(state) == BOTH;
  }

  void Automaton::setStateFinal(int state) {
    if (!hasState(state)) return;
    if (isStateFinal(state)) return;
    if (isStateInitial(state)) {
      states[state] = BOTH;
      return;
    }
    states[state] = FINAL;
  }

  bool Automaton::isStateFinal(int state) const {
    if (states.count(state) == 0) return false;
    return states.at(state) == FINAL || states.at(state) == BOTH;
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to)) return false;
    if (!hasState(from)) return false;
    if (!hasState(to)) return false;
    if (!hasSymbol(alpha) && alpha != fa::Epsilon) return false;
    transitions.insert(std::make_tuple(from, alpha, to));
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasTransition(from, alpha, to)) return false;
    transitions.erase(std::make_tuple(from, alpha, to));
    return true;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    return transitions.count(std::make_tuple(from, alpha, to)) == 1;
  }

  std::size_t Automaton::countTransitions() const{
    return transitions.size();
  }

  void Automaton::prettyPrint(std::ostream& os) const{
    os << "Initial states : "<< std::endl;
    for (auto state : states) {
      if(isStateInitial(state.first)){
        os << state.first << " ";
      }
    }
    os << std::endl;
    os << "Final states : " << std::endl;
    for (auto state : states) {
      if(isStateFinal(state.first)){
        os << state.first << " ";
      }
    }
    os << std::endl;
    os << "Transitions:" << std::endl;
    for (auto state : states) {
      os << "For state " << state.first << ":" << std::endl;
      for (auto c : alphabet) {
        os << "  For letter " << c << ": ";
        for (const auto &i : transitions){
          if((state.first == std::get<0>(i)) && (c==std::get<1>(i))){
            os << std::get<2>(i) << " ";
          }
        }
        os << std::endl;
      }
    }
    return ;
  }

  bool Automaton::hasEpsilonTransition() const {
    for (auto state : transitions) {
      if (std::get<1>(state) == (fa::Epsilon))
        return true;
    }
    return false;
  }

  bool Automaton::isDeterministic() const {
    int cptInitial = 0;
    int cptFinal = 0;
    for (auto state : states) {
      if (state.second == INITIAL || state.second == BOTH) {
        cptInitial++;
      }
      if (state.second == FINAL || state.second == BOTH) {
        cptFinal++;
      } 
    }
    if (cptInitial != 1) return false;
    if (cptFinal < 1) return false;
    for (auto current : transitions) {
      for (auto check : transitions) {
        if (check == current) continue;
        if (std::get<0>(current) == std::get<0>(check)) {
          if (std::get<1>(current) == std::get<1>(check)) {
            return false;
          }
        }
      }
    }
    return true;
  }

  bool Automaton::isComplete() const {
      for (const auto& state : states) {
        int s = state.first;
        for (char c : alphabet) {
          bool found = false;
          for (const auto& t : transitions) {
            if (std::get<0>(t) == s && std::get<1>(t) == c) {
              found = true;
              break;
            }
          }
          if (!found) return false;
        }
      }
      return true;
    }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    if (automaton.isComplete()) return automaton;
    Automaton comp = automaton;
    auto it = std::prev(comp.states.end());
    int newState = it->first + 1;
    comp.addState(newState);
    for (char c : comp.alphabet) {
      comp.addTransition(newState, c, newState);
    }
    for (const auto& state : comp.states) {
        int s = state.first;
        for (char c : comp.alphabet) {
          bool found = false;
          for (const auto& t : comp.transitions) {
            if (std::get<0>(t) == s && std::get<1>(t) == c) {
              found = true;
              break;
            }
          }
          if (!found) comp.addTransition(s, c, newState);
        }
      }
    return comp;
  }

  Automaton Automaton::createComplement(const Automaton& automaton) {
    return automaton;
  }

  Automaton Automaton::createMirror(const Automaton& automaton) {
    Automaton mirror = automaton;

    std::set<int> tempInitial;
    std::set<int> tempFinal;
    for (auto state : mirror.states) {
      if(mirror.isStateInitial(state.first)){
        tempFinal.insert(state.first);
      }
    }

    for (auto state : mirror.states) {
      if(mirror.isStateFinal(state.first)){
        tempInitial.insert(state.first);
      }
    }

    for (auto state : tempInitial) {
      mirror.states[state] = INITIAL;
    }

    for (auto state : tempFinal) {
      if (mirror.states[state] == INITIAL) {
        mirror.states[state] = BOTH;
      } else {
        mirror.states[state] = FINAL;
      }
    }

    for (auto tuple : automaton.transitions) {
      mirror.addTransition(std::get<2>(tuple), std::get<1>(tuple), std::get<0>(tuple));
    }

    return mirror;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> result;
    for (auto from : origin) {
      for (auto current : states) {
        if (hasTransition(from, alpha, current.first))
          result.insert(current.first);
      }
    }
    return result;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    std::set<int> path;
    for (auto state : states) {
      if (state.second == INITIAL || state.second == BOTH) {
        path.insert(state.first);
      }
    }
    for (auto c : word) {
      path = makeTransition(path, c);
    }
    return path;
  }

  bool Automaton::match(const std::string& word) const {
    std::set<int> match = readString(word);
    bool stateFinal = false;
    for (auto state : match) {
      if (isStateFinal(state)) stateFinal = true;
    }
    if (!stateFinal) return false;
    return true;
  }

  bool Automaton::isLanguageEmpty() const {
    std::vector<int> queue;
    std::set<int> visited;

    for (auto s : states) {
      if (isStateInitial(s.first)) {
          queue.push_back(s.first);
          visited.insert(s.first);
      }
    }
    while (!queue.empty()) {
      int state = queue.back();
      queue.pop_back();
      if (isStateFinal(state)) {
        return false;
      }
      for (auto t : transitions) {
        if (std::get<0>(t) == state) {
          int next = std::get<2>(t);
          if (visited.find(next) == visited.end()) {
            queue.push_back(next);
            visited.insert(next);
          }
        }
      }
    }
    return true;
  }

  // Automate doit reste valide sauf si il n'a pas d'état initial ?
  void Automaton::removeNonAccessibleStates() {
    std::vector<int> queue;
    std::set<int> visited;

    for (auto s : states) {
      if (isStateInitial(s.first)) {
          queue.push_back(s.first);
          visited.insert(s.first);
      }
    }
    while (!queue.empty()) {
      int state = queue.back();
      queue.pop_back();
      for (auto t : transitions) {
        if (std::get<0>(t) == state) {
          int next = std::get<2>(t);
          if (visited.find(next) == visited.end()) {
            queue.push_back(next);
            visited.insert(next);
          }
        }
      }
    }
    std::vector<int> remove;
    for (auto current : states) {
      if (visited.find(current.first) == visited.end()) {
        remove.push_back(current.first);
      }
    }
    for (auto rm : remove) {
      removeState(rm);
    }
  } 

  // Automate doit reste valide sauf si il n'a pas d'état initial ?
  void Automaton::removeNonCoAccessibleStates() {
    std::vector<int> queue;
    std::set<int> visited;

    for (auto s : states) {
      if (isStateFinal(s.first)) {
          queue.push_back(s.first);
          visited.insert(s.first);
      }
    }
    while (!queue.empty()) {
      int state = queue.back();
      queue.pop_back();
      for (auto t : transitions) {
        if (std::get<2>(t) == state) {
          int next = std::get<0>(t);
          if (visited.find(next) == visited.end()) {
            queue.push_back(next);
            visited.insert(next);
          }
        }
      }
    }
    std::vector<int> remove;
    for (auto current : states) {
      if (visited.find(current.first) == visited.end()) {
        remove.push_back(current.first);
      }
    }
    for (auto rm : remove) {
      removeState(rm);
    }
  }

  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
    return false;
  }

  bool Automaton::isIncludedIn(const Automaton& other) const {
    return false;
  }

  Automaton Automaton::createIntersection(const Automaton& lhs, const Automaton& rhs) {
    Automaton first = lhs;
    Automaton second = rhs;
    Automaton final;

    if (!first.isDeterministic()) first = Automaton::createDeterministic(first);
    if (!second.isDeterministic()) second = Automaton::createDeterministic(second);

    for (char c : second.alphabet) first.addSymbol(c);
    for (char c : first.alphabet) second.addSymbol(c);
    final.alphabet = first.alphabet;
    
    if (!first.isComplete()) first = Automaton::createComplete(first);
    if (!second.isComplete()) second = Automaton::createComplete(second);

    std::set<int> nextFirst;
    std::set<int> nextSecond;

    int firstInitial = 0;
    int secondInitial = 0;
    for (auto s : first.states) {
      if (first.isStateInitial(s.first)) {
        firstInitial = s.first;
        nextFirst.insert(s.first);
        break;
      }
    }
    for (auto s : second.states) {
      if (second.isStateInitial(s.first)) {
        secondInitial = s.first;
        nextSecond.insert(secondInitial);
        break;
      }
    }

    int cpt = 0;
    std::map<std::pair<int, int>, int> translate;
    std::vector<std::pair<int, int>> queue;
    queue.push_back({firstInitial, secondInitial});

    translate.insert({{firstInitial, secondInitial}, cpt});
    final.addState(0);
    final.setStateInitial(0);
    cpt++;

    while (!queue.empty()) {
      std::pair<int, int> current = queue.front();
      queue.erase(queue.begin());
      int stateA = current.first;
      int stateB = current.second;
      int newStart = translate[current];
      for (char c : final.alphabet) {
        std::set<int> nextStateA = first.makeTransition({stateA}, c);
        int newStateA = *nextStateA.begin();
        std::set<int> nextStateB = second.makeTransition({stateB}, c);
        int newStateB = *nextStateB.begin();

        std::pair<int, int> newCouple = {newStateA, newStateB};
        if (translate.count(newCouple) == 0) {
          translate.insert({newCouple, cpt});
          final.addState(cpt);
          if (first.isStateFinal(newStateA) && second.isStateFinal(newStateB)) final.setStateFinal(cpt);
          cpt++;
          queue.push_back(newCouple);
        }
        int newTarget = translate[newCouple];
        final.addTransition(newStart, c, newTarget);
      }
    }
    return final;
  }

  Automaton Automaton::createDeterministic(const Automaton& other) {
    return other;
  }

  Automaton Automaton::createMinimalMoore(const Automaton& other) {
    return other;
  }

  Automaton Automaton::createMinimalBrzozowski(const Automaton& other) {
    return other;
  }
}

