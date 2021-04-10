import React from "react";
import Board from "./Board";

export default class Game extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            history: [
                Array(9).fill(null),
            ],
            xIsNext: true,
            stepNumber: 0,
        }
    }

    jumpTo(move) {
        this.setState({
            stepNumber: move,
            xIsNext: (move % 2) === 0,
        });
    }

    handleSquareClick(i) {
        if (this.state.stepNumber === 9) {
            console.log("Game finished.")
            return;
        }
        const history = this.state.history.slice(
            0, this.state.stepNumber + 1
        );
        const squares = history[history.length - 1].slice();
        if (calculateWinner(squares) || squares[i]) {
            return;
        }
        squares[i] = this.state.xIsNext ? 'X' : 'O';
        this.setState({
            history: history.concat([squares]),
            xIsNext: !this.state.xIsNext,
            stepNumber: history.length,
        });
    }

    render() {
        const history = this.state.history;
        const squares = history[this.state.stepNumber];
        const moves = history.map((step, move) => {
            const desc = move ?
                'Go to move #' + move :
                'Go to game start';
            return (
                <li key={move}>
                    <button
                        className={this.state.stepNumber === move ? 'currentMove' : 'move'}
                        onClick={() => this.jumpTo(move)}>
                        {desc}
                    </button>
                </li>
            );
        });

        let status;
        const winner = calculateWinner(squares);
        if (winner) {
            status = 'Winner: ' + winner;
        }
        else if (this.state.stepNumber === 9) {
            status = 'Draw';
        }
        else {
            status = 'Next player: '
                + (this.state.xIsNext ? 'X' : 'O');
        }


        return (
            <div className="game">
                <div className="game-board">
                    <Board
                        squares={squares}
                        onClick={(i) => this.handleSquareClick(i)}
                    />
                </div>
                <div className="game-info">
                    <div>{status}</div>
                    <ol>{moves}</ol>
                </div>
            </div>
        );
    }
}

function calculateWinner(squares) {
    const lines = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6],
    ];
    for (let i = 0; i < lines.length; i++) {
        const [a, b, c] = lines[i];
        if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
            return squares[a];
        }
    }
    return null;
}
