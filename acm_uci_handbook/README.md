# ACM@UCI Handbook

## About
The ACM@UCI Handbook is intended to be a printable resource for use at in person contests such as ICPC.

## Rules
* This project is free and open source (not licensed)
    * Anyone is free to use/modify the ACM@UCI Handbook as the please
* For this specific repository, published credit will only be granted with the permission of the repository admin: Ryan Yoshida
* Pull requests of any kind are highly encouraged: typos, grammar, formatting, algorithm mistakes, etc.

## Organization
* The document is broken into two sections: **Data Structures** and **Algorithms**
    * Keep these sections consistent as much as possible
    * If an algorithm requires a non-standard data structure (not included in the relevant standard library) provide a `\ref` to that data structure
* Sub-sections are organized in alphabetical order
* Sub-sub-sections are organized in alphabetical order
* Every algorithm includes a brief description of **the algorithm's purpose** and the **time complexity**
* Keep wording as concise as possible

## Building
* A `Makefile` is provided in the directory
    * It runs `pdflatex` which is from the [Tex Live package](https://tug.org/texlive/)
        * On Arch Linux install `texlive-core`
        * For Windows refer to [this](https://tug.org/texlive/windows.html)
