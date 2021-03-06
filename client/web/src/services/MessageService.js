import {addCommandProcessor} from 'services/CommunicationService'
import takeRight from 'lodash/takeRight'
import {updateNode} from "./NodeService";

const messages = observable.shallowArray([]);

addCommandProcessor('messages', action('messages', arr => arr.forEach(m => messages.push(m))));

(function() {
    let lastReceivedMessageIdx;
    setInterval(() => {
        const newMessages = takeRight(messages, messages.length - lastReceivedMessageIdx);
        lastReceivedMessageIdx = messages.length;
        newMessages.reduce((result, message) => {
            result.add(message.srcAddr);
            result.add(message.dstAddr);
            return result;
        }, new Set())
            .forEach(address => updateNode({address: address, lastMessageReceived: new Date().getTime()}));
    }, 700);
}());

export const getMessages = () => messages;