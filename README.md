# libmemcached

[![Build Status](https://travis-ci.org/tomi77/node-libmemcached.svg?branch=master)](https://travis-ci.org/tomi77/node-libmemcached)

Node.js bindings to the [libMemcached](http://libmemcached.org/) library.

## Table of contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [API](#api)
  * [get(key: string): Buffer](#getkey-string-buffer)
  * [exist(key: string): boolean](#existkey-string-boolean)
  * [touch(key: string, expiration: integer): this](#touchkey-string-expiration-integer-this)
  * [delete(key: string): this](#deletekey-string-this)
  * [increment(key: string, offset?: integer=1): integer](#incrementkey-string-offset-integer1-integer)
  * [decrement(key: string, offset?: integer=1): integer](#decrementkey-string-offset-integer1-integer)

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

### get(key: string): Buffer

Get item.

### exist(key: string): boolean

Determine if a item exists.

### touch(key: string, expiration: integer): this

Update the expiration time of an existing item without fetching it.

### delete(key: string): this

Remove a item.

### increment(key: string, offset?: integer=1): integer

Incrementing item.

### decrement(key: string, offset?: integer=1): integer

Decrementing item.
