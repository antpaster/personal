//
//  FrameQueue.swift
//  Mobistreamer
//
//  Created by Александр on 05.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

fileprivate func < <T : Comparable>(lhs: T?, rhs: T?) -> Bool {
    switch (lhs, rhs) {
    case let (l?, r?):
        return l < r
    case (nil, _?):
        return true
    default:
        return false
    }
}

protocol FrameQueueStorage {
    func bufferFlush(video:[FrameEntity], audio:[FrameEntity], ts:Int)
}

protocol FrameQueueSignal {
    func bufferFlush()
}

protocol Queue {
    var storage:FrameQueueStorage? {get set}
    var queueSignalDelegate:FrameQueueSignal? {get set}

    func push(_ item:FrameEntity)
    func flush()
    func pop() -> FrameEntity?
    func clear()
}

class ConcurrentQueque: Queue {

    var storage:FrameQueueStorage?
    var queueSignalDelegate:FrameQueueSignal?

    let max_size = 100
    let bufferSize = 8

    var videoItems = [FrameEntity]() // bool is true
    var audioItems = [FrameEntity]() // bool is false

    var serialQueue:DispatchQueue?

    var videoSemaphore = DispatchSemaphore(value: 1)
    var audioSemaphore = DispatchSemaphore(value: 1)

    func push(_ item: FrameEntity) {
        if item.type == .video {
            pushVideo(item)
        }else if item.type == .audio {
            pushAudio(item)
        }
    }

    func pushVideo(_ item: FrameEntity) {
        switch self.videoItems.count {
        case 0...30:
            break
        case 31...60:
            break
        case 61...100:
            break
        default:
            break
        }

        videoSemaphore.wait()
        if self.videoItems.count > max_size {
            print("BUFER FLUSH")
            flush()
        }
        self.videoItems.append(item)
        videoSemaphore.signal()
    }

    func pushAudio(_ item: FrameEntity) {
        audioSemaphore.wait()
        self.audioItems.append(item)
        audioSemaphore.signal()
    }

    func flush() {

        var v = [FrameEntity]()
        var a = [FrameEntity]()

        if self.videoItems.count > 0 {
            v = self.videoItems
            self.videoItems = [FrameEntity]()
        }

        audioSemaphore.wait()
        if self.audioItems.count > 0 {
            a = self.videoItems
            self.audioItems = [FrameEntity]()
        }
        audioSemaphore.signal()

        storage?.bufferFlush(video: v, audio: a, ts: FrameManager.lastTs)
        queueSignalDelegate?.bufferFlush()
    }

    func pop() -> FrameEntity? {
        if videoItems.count < bufferSize {
            return nil
        }

        if topAudioItem == nil {
            if videoItems.count > 0 {
                videoSemaphore.wait()
                let ass:FrameEntity = videoItems.removeFirst()
                videoSemaphore.signal()
                return ass
            }
            return nil
        }

        if topVideoItem == nil {
            return nil
        }

        if topAudioItem?.ts < topVideoItem?.ts {
            audioSemaphore.wait()
            let ass:FrameEntity = audioItems.removeFirst()
            audioSemaphore.signal()
            return ass
        } else {
            videoSemaphore.wait()
            let ass:FrameEntity = videoItems.removeFirst()
            videoSemaphore.signal()
            return ass
        }
    }

    var topVideoItem: FrameEntity? {
        var frame:FrameEntity? = nil
        videoSemaphore.wait()
        frame = videoItems.isEmpty ? nil : videoItems[0]
        videoSemaphore.signal()
        return frame
    }

    var topAudioItem: FrameEntity? {
        var frame:FrameEntity? = nil
        audioSemaphore.wait()
        frame = audioItems.isEmpty ? nil : audioItems[0]
        audioSemaphore.signal()
        return frame
    }

    func clear() {
        print("CLEAR ALL!")
        videoItems.removeAll()
        audioSemaphore.wait()
        audioItems.removeAll()
        audioSemaphore.signal()
    }
}
