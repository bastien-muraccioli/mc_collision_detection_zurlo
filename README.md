mc_rtc Collision Detection Zurlo plugin
==

This project is a [mc_rtc] plugin implementing the collision detection method from the paper:

Collision Detection and Contact Point Estimation Using Virtual Joint Torque Sensing Applied to a Cobot.

This implementation focuses only on collision detection and does not include contact point estimation. It has been implemented and tested on the Kinova Gen 3 collaborative robot (cobot).

# Requirements

This plugin depends on the following mc_rtc plugins:

- [mc_current_residual](https://github.com/bastien-muraccioli/mc_current_residual)
- [mc_energy_residual](https://github.com/bastien-muraccioli/mc_energy_residual)

# References

D. Zurlo, T. Heitmann, M. Morlock and A. De Luca, "Collision Detection and Contact Point Estimation Using Virtual Joint Torque Sensing Applied to a Cobot," 2023 IEEE International Conference on Robotics and Automation (ICRA), London, United Kingdom, 2023, pp. 7533-7539, doi: 10.1109/ICRA48891.2023.10160661. keywords: {Torque;Atmospheric measurements;Service robots;Current measurement;Estimation;Robot sensing systems;Particle measurements},

# Author

This implementation was developed by Bastien Muraccioli and is not affiliated with the original authors of the referenced paper.

[mc_rtc]: https://jrl-umi3218.github.io/mc_rtc/
