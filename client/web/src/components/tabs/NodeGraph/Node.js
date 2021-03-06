import nodeColors from 'constants/nodeStatusColors'

const Node = ({node, onMouseOver, selected}) => {
    const {address, nodeState, xAngle, yAngle} = node;
    const cx = 90 * xAngle + 100;
    const cy = 90 * yAngle + 100;

    const r = new Date().getTime() - node.lastMessageReceived < 700 ? '8' : '6';
    return node.isLeader ? (
        <g id={`node=${address}`} onMouseOver={onMouseOver}>
            <linearGradient id={`gradient-${address}`} key={`gradient-${address}`} fx="60%" fy="40%">
                <stop stopColor={nodeColors[nodeState]} offset="75%"/>
                <stop stopColor="#999" offset="100%"/>
            </linearGradient>
            <rect fill={`url(#gradient-${address})`} key={`circle-${address}`} x={cx - r} y={cy - r} height={r*2} width={r*2}/>
        </g>

    ) : (
        <g id={`node-${address}`} onMouseOver={onMouseOver}>
            <radialGradient id={`gradient-${address}`} key={`gradient-${address}`} fx="60%" fy="40%">
                <stop stopColor={nodeColors[nodeState]} offset="75%"/>
                <stop stopColor="#999" offset="100%"/>
            </radialGradient>
            <circle fill={`url(#gradient-${address})`} key={`circle-${address}`}  cx={cx} cy={cy} r={r}/>
            {selected && <circle fill='white' key={`circle-border=${address}`} cx={cx} cy={cy} r="2"/>}
        </g>
    )
};

export default Node

