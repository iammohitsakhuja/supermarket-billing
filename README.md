# Supermarket Billing

This repository contains a project for a CLI based Supermarket billing system,
written in C++. It utilizes a SQLite database to keep track of previous
transactions and the inventory items.

## Demo

![supermarket-billing-demo](https://user-images.githubusercontent.com/30660843/48360339-031d5580-e6c5-11e8-90ff-0b915775189b.gif)

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development.

### Requirements

- `C++11` (or above) compiler
- `SQLite` library
- `make` utility

### Installation steps

To install `SQLite`, use `apt-get` on Linux, `brew` on macOS.

Once you have installed all the requirements, run the following:

```bash
$ sqlite3 supermarket.db < items.sql
$ sqlite3 supermarket.db < orders.sql
$ make
$ ./billing
Welcome to our supermarket!
```
