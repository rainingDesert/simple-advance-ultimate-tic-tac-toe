### Readme
### Readme

---
#### 1. Creater
Guofeng(Evan) Cui
#### 2. Briefly Introduction
1. Current Edition: initial edition, that can run *simple tic-tac-toe/ advanced tic-tac-toe/ ultimate tic-tac-toe* with strategy including **alphabeta**, **H-minimum** as well as **Monte Carlo Game Tree**.
2. Project is still waiting to be updated for readable, optimization for efficiency.
3. Next jobs expectedly:
1) optimize structure of code
2) optimize strategy

--- 
#### 3. Build the program
1. build alphabeta for simple tic-tac-toe: 
g++ TTTUI.cpp ATTTUI.cpp UTTTUI.cpp Game.cpp simpleTTT.cpp advanceTTT.cpp ultimateTTT.cpp UCT.cpp UCTForUltimate.cpp UCTForAdvanced.cpp Stratagem_alphaBeta.cpp Imp.cpp execSimple.cpp -o run.out
2. build alphabeta for advanced tic-tac-toe:
g++ TTTUI.cpp ATTTUI.cpp UTTTUI.cpp Game.cpp simpleTTT.cpp advanceTTT.cpp ultimateTTT.cpp UCT.cpp UCTForUltimate.cpp UCTForAdvanced.cpp Stratagem_alphaBeta.cpp Imp.cpp execAdvancedH.cpp -o run.out
3. build UCT for advance tic-tac-tie:
g++ TTTUI.cpp ATTTUI.cpp UTTTUI.cpp Game.cpp simpleTTT.cpp advanceTTT.cpp ultimateTTT.cpp UCT.cpp UCTForUltimate.cpp UCTForAdvanced.cpp Stratagem_alphaBeta.cpp Imp.cpp execAdvancedU.cpp -o run.out 
4. build alphabeta for ultimate tic-tac-toe:
g++ TTTUI.cpp ATTTUI.cpp UTTTUI.cpp Game.cpp simpleTTT.cpp advanceTTT.cpp ultimateTTT.cpp UCT.cpp UCTForUltimate.cpp UCTForAdvanced.cpp Stratagem_alphaBeta.cpp Imp.cpp execUltimateH.cpp -o run.out
5. build UCT for ultimate tic-tac-toe:
g++ TTTUI.cpp ATTTUI.cpp UTTTUI.cpp Game.cpp simpleTTT.cpp advanceTTT.cpp ultimateTTT.cpp UCT.cpp UCTForUltimate.cpp UCTForAdvanced.cpp Stratagem_alphaBeta.cpp Imp.cpp execUltimateU.cpp -o run.out
#### 4. Run the program
./run.out