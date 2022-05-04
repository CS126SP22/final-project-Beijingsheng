<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="https://firebasestorage.googleapis.com/v0/b/clone-drive-eb3d3.appspot.com/o/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20220504021519.png?alt=media&token=26db817c-5ca0-402f-a5eb-181b74d92270" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Mini Cargo Simulator</h3>

  <p align="center">
    An awesome visualizer for you to simulate cargo carriers!
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

Wanna figure out if your cargo carrying system is well designed? Mini Cargo Simulator is the right solution. This is the app that perfectly suits your need to measure, analyze, and improve your cargo carrying system.

Here's why:
* By editing three json files, you will have a perfectly visualization of how well the cargo carrying system you designed performs in various situations.
* You will be able to measure the rationality of the placement of your cargo stations, the route of your carriers, and the designated departures and destinations.
* Improving your design and generate new visualization as easy as modifying values in json files.

Of course, no one simulator will serve all your needs. You may also suggest changes by connecting with me at clarklubeijing at gmail dot com. So I'll be adding more requested features in the near future. 

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

This is a list of all the major frameworks/libraries/editors used to develop this simulator.

* [CLion](https://www.jetbrains.com/clion/)
* [Cinder](https://libcinder.org/)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may set up and use the simulator locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* [Install CLion and Cinder](https://courses.grainger.illinois.edu/cs126/sp2022/notes/cinder-installation-notes/)


### Installation

* Create a directory called my-projects in your Cinder folder. Navigate to the my-projects folder and clone this repository within it, and then open the repository using CLion. You should be able to run two different targets; make sure that both of them work.

<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

To simulate a scenario, you would need to edit three json files in the resources folder.
* One that refers to all the stations, including their connections and locations
* One that refers to all the metros/carriers, including their routes and colors
* One that refers to all the cargos, including their color, start stations, and destinations
Play around by editing these files, see what you get by building the mini-metro.

Features for you to explore in the GUI:
* Click on each cargo, carrier, and station to see the message displayed on top.
* Two numbers are displayed above the message, representing the moves needed before all cargo arrives at their destinations, and the total moves needed.
* Speed up and slow down the carriers, pause and resume the system.

<p align="right">(<a href="#top">back to top</a>)</p>
