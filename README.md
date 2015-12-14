# Bowling-Score-Calculator
Keep score of a bowling game for a given player. Traditional game with 10 Frames, Two rounds, with an extra round on last frame. 
*** What does the Application do? ***
  ` It takes in the amount of pins knocked down on each turn and outputs a scoreboard. `

*** Strategy ***
  ` First check if we have a strike: 
      if (yes) 
        Then save a boolean like indicator that tells the program to save the previous frame. 
      else
        Then we move on and check if we have an open_frame or a spare. 
      end `
  
  Always save the previous turn points to help update a strike frame or a spare frame. 
  
