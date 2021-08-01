<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

Program that counts the number of distinct unique words in a file.
To be able to work with large files IO is organized with memory mapping.
For Unix and Windows platforms it uses corresponding system calls.
To utilize all available CPU resources multithreading actively used.
Utility does not expect other word delimeter than blank whitespace.

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* cmake
  ```sh
  https://cmake.org/install/
  ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/avtyshcuk/WordsCount.git
   ```
2. Clone gtest submodule for testing
   ```sh
   git submodule init
   git submodule update
   ```


<!-- USAGE EXAMPLES -->
## Usage

./WordsCounter inputFile
./WordsCounterTest -> for testing



<!-- ROADMAP -->
## Roadmap

To simplify multithreading approach main thread capabilities are not explicitly used - program creates +1 thread
To be aligned by word's edge iteration till blank whitespace is performed, for "one long word" it may be slow


