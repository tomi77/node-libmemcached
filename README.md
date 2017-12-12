# libmemcached

[![Build Status](https://travis-ci.org/tomi77/node-libmemcached.svg?branch=master)](https://travis-ci.org/tomi77/node-libmemcached)

Node.js bindings to the [libMemcached](http://libmemcached.org/) library.

## Table of contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [API](#api)
  * [get(key : String) : Buffer](#getkey--string--buffer)
  * [exist(key : String) : Boolean](#existkey--string--boolean)
  * [touch(key : String, expiration : Integer) : this](#touchkey--string-expiration--integer--this)
  * [delete(key : String) : this](#deletekey--string--this)
  * [increment(key : String [, offset : Integer = 1]) : Integer](#incrementkey--string--offset--integer--1--integer)
  * [decrement(key : String [, offset : Integer = 1]) : Integer](#decrementkey--string--offset--integer--1--integer)

## Requirements

* `libmemcached`
* `libmemcached-dev`
* `gcc`

## Installation

~~~sh
npm install libmemcached --save
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

### get(key : String) : Buffer

Get item.

### exist(key : String) : Boolean

Determine if a item exists.

### touch(key : String, expiration : Integer) : this

Update the expiration time of an existing item without fetching it.

### delete(key : String) : this

Remove a item.

### increment(key : String [, offset : Integer = 1]) : Integer

Incrementing item.

### decrement(key : String [, offset : Integer = 1]) : Integer

Decrementing item.
