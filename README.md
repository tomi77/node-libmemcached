# libmemcached

[![Build Status](https://travis-ci.org/tomi77/node-libmemcached.svg?branch=master)](https://travis-ci.org/tomi77/node-libmemcached)

Node.js bindings to the [libMemcached](http://libmemcached.org/) library.

## Table of contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [API](#api)
  * [`get(key : String) : Buffer`](#getkey--string--buffer)
  * [`exist(key : String) : Boolean`](#existkey--string--boolean)
  * [`touch(key : String, expiration : Number)`](#touchkey--string-expiration--number)
  * [`delete(key : String)`](#deletekey--string)

## Requirements

* `libmemcached`
* `libmemcached-dev`
* `gcc`

## Installation

~~~sh
npm i libmemcached
~~~

or

~~~sh
yarn add libmemcached
~~~

## Usage

~~~js
const MemcachedClient = require('libmemcached');

const mcc = new MemcachedClient('--SERVER=127.0.0.1');

console.log(mcc.get('test'));
~~~

## API

### `get(key : String) : Buffer`

Get item.

### `exist(key : String) : Boolean`

Determine if a item exists.

### `touch(key : String, expiration : Number)`

Update the expiration time of an existing item without fetching it.

### `delete(key : String)`

Remove a item.
