#!/usr/bin/env python2
# coding: utf-8

# This file is mostly copied from https://github.com/dprgarner/oapy .

import argparse
import json
import sys
from random import choice
from subprocess import check_output
from os.path import dirname, join

from websocket import create_connection


class Client(object):
    SIZE = 15
    GAME_TYPE = 'Gomoku'

    def __init__(self):
        self.set_args()
        self.connect()

    def send(self, msg):
        """
        All messages to the server must be JSON-serialisable.
        """
        self.ws.send(json.dumps(msg))

    def recv(self):
        """
        All messages from the server are valid JSON.
        """
        msg = self.ws.recv()
        return (
            json.loads(msg)
            if msg
            else msg
        )

    def set_args(self):
        parser = argparse.ArgumentParser(
            description='Python Client for Aoire'
        )
        parser.add_argument(
            '--hostname',
            type=str,
            # default='hub.nechifor.net:8443',
            default='localhost',
            help='The location of the server, e.g. "localhost:3000".',
        )
        parser.add_argument(
            '--user',
            type=str,
            default='Coaie (by Paul)',
            help='The bot name and owner, e.g. "BotName (by David)".',
        )
        parser.add_argument(
            '--room',
            type=str,
            default='coaie',
            help='Where you agree to meet with another player.',
        )
        parser.add_argument(
            '--ngames',
            type=int,
            default=1,
            help='The number of consecutive games to play.',
        )
        args = parser.parse_args()
        for k, v in args._get_kwargs():
            setattr(self, k, v)

    def recv_type(self, type_):
        """
        Assert that the correct message is received.
        """
        msg = self.recv()
        assert msg and msg['type'] == type_, msg
        sys.stdout.write('.')
        return msg

    def connect(self):
        try:
            self.ws = create_connection('ws://{}/game'.format(self.hostname))
            print('Bot connected - waiting to start game...')
            self.send({
                'type': 'StartGame',
                'room': self.room,
                'userAgent': self.user,
                'gameType': self.GAME_TYPE,
                'nGames': self.ngames,
            })
            self.index = self.recv_type('YouAre')['index']

            for i in range(self.ngames):
                self.recv_type('Started')
                print('Game {} started'.format(i + 1))
                self.play_game((self.index + i) % 2 == 0)
        finally:
            if hasattr(self, 'ws') and self.ws.connected:
                self.ws.close()

    def play_game(self, is_first_player):
        """
        A simple memoryless implementation of a Gomoku game-playing bot.
        Modify this if you want to do something fancy.
        (The first player is -1, the second player is 1).
        """
        state = [0] * (self.SIZE * self.SIZE)
        turn_number = 0
        player_number = -1 if is_first_player else 1

        print('Your bot is playing {} ({})'.format(
            'first' if is_first_player else 'second',
            'black' if self.index == 0 else 'white'
        ))
        try:
            for turn_number in range(self.SIZE * self.SIZE):
                is_my_turn = bool(turn_number % 2) != is_first_player

                if is_my_turn:
                    turn_space = self.play_turn(state, player_number)
                    self.send({'type': 'Move', 'move': turn_space})

                update = self.recv_type('PlayerMove')
                state[update['move']] = (
                    player_number if is_my_turn else -player_number
                )
                if 'winner' in update:
                    won = self.index == update.get('winner')
                    if update.get('winner') == -2:
                        print('\nThe game was a draw.')
                    else:
                        print('\nYour bot has {} the game'.format(
                            'won' if won else 'lost'
                        ))
                    return
        finally:
            is_first_player_black = (
                is_first_player and self.index == 0 or
                not is_first_player and self.index == 1
            )
            print(self.render_state(state, is_first_player_black))

    def render_state(self, state, is_first_player_black):
        """
        Return a pretty string representation of the board.
        """
        MOVES_STR = {
            -1 if is_first_player_black else 1: '▒▒',
            0: '  ',
            1 if is_first_player_black else -1: '██',
        }

        numbers = '   ' + ''.join(
            str(i) + (' ' if i < 10 else '')
            for i in range(self.SIZE)
        )
        top = '  ╔' + ('══' * self.SIZE) + '╗'
        bottom = '  ╚' + ('══' * self.SIZE) + '╝'

        collated_string = '{}\n{}\n{}\n{}'.format(
            numbers,
            top,
            '\n'.join([
                '{}║{}║'.format(
                    (' ' if i < 10 else '') + str(i),
                    ''.join([
                        MOVES_STR[state[self.SIZE * i + j]]
                        for j in range(self.SIZE)
                    ]),
                )
                for i in range(self.SIZE)
            ]),
            bottom,
        )
        return collated_string

    def play_turn(self, state, player):
        code = {1: 'x', 0: '.', -1: 'o'}
        board = ''.join(code[x] for x in state)
        executable = join(dirname(__file__), 'coaie')
        args = [executable, 'play', board, code[player]]
        return choice(map(int, check_output(args).strip().split(' ')))


if __name__ == '__main__':
    Client()
