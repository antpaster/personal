//
//  UploadOperationQueue.swift
//  Mobistreamer
//
//  Created by Александр on 21.06.17.
//  Copyright © 2017 Netris. All rights reserved.
//

import UIKit

class ProgressState {
    var partCount:Int = 0
    var currentPart:Int = 0
    var currentPartDataSize:Int = 0
    var currentPartUploadedSize:Int = 0
}

protocol UploadOperationQueueOutput {
    func message(text:String)
    func progress(state:ProgressState)
    func status(status:UploadOperationQueueStatus)
}

enum UploadOperationQueueStatus {
    case none
    case upload
    case stop(error:Error?)
}

class UploadOperationQueue: NSObject {

    var operationQueue:[UploadOperation] = [UploadOperation]()
    var sessions:[StorageSessionTransport] = [StorageSessionTransport]()
    var currentOperation = 0

    var output:UploadOperationQueueOutput?

    var operation:UploadOperation?
    var canceled = false
    var status:UploadOperationQueueStatus = .none

    func cancel() {
        self.canceled = true
        self.operation?.cancel()
    }

    func run() {
        self.canceled = false

        currentOperation = 0
        if currentOperation >= sessions.count {
            return
        }
        let progressStateItem:ProgressState = ProgressState()
        progressStateItem.currentPart = currentOperation
        progressStateItem.currentPartDataSize = 0
        progressStateItem.partCount = sessions.count
        progressStateItem.currentPartUploadedSize = 0
        output?.progress(state: progressStateItem)

        self.operation = UploadOperation(session: sessions[currentOperation], progress:{ (sent, size) in
            let progressStateItem:ProgressState = ProgressState()
            progressStateItem.currentPart = self.currentOperation
            progressStateItem.currentPartDataSize = size
            progressStateItem.partCount = self.sessions.count
            progressStateItem.currentPartUploadedSize = sent
            self.output?.progress(state: progressStateItem)
        } , success: { (obj) in
            if let obj = obj {
                self.output?.message(text: "to send:\(obj["towrite"] as! Int) sent:\(obj["writed"] as! Int)")
            }
            self.next()
        }) { (error) in
            if self.canceled {
                self.status = .stop(error: nil)
                self.output?.status(status: self.status)
                return
            }
            self.output?.message(text: "Error: \(error?.localizedDescription)")
            self.next()
        }
        self.status = .upload
        self.output?.status(status: self.status)
        operation?.main()
    }

    func next() {
        if canceled {
            self.status = .stop(error: nil)
            self.output?.status(status: self.status)
            return
        }
        sleep(1)
        currentOperation += 1
        if currentOperation >= sessions.count {
            self.status = .stop(error: nil)
            self.output?.status(status: self.status)
            return
        }

        let progressStateItem:ProgressState = ProgressState()
        progressStateItem.currentPart = currentOperation
        progressStateItem.currentPartDataSize = 0
        progressStateItem.partCount = sessions.count
        progressStateItem.currentPartUploadedSize = 0
        self.output?.progress(state: progressStateItem)

        self.operation = UploadOperation(session: sessions[currentOperation], progress: { (sent, size) in
            let progressStateItem:ProgressState = ProgressState()
            progressStateItem.currentPart = self.currentOperation
            progressStateItem.currentPartDataSize = size
            progressStateItem.partCount = self.sessions.count
            progressStateItem.currentPartUploadedSize = sent
            self.output?.progress(state: progressStateItem)
        } , success: { (obj) in
            if let obj = obj {
                self.output?.message(text: "to send:\(obj["towrite"] as! Int) sent:\(obj["writed"] as! Int)")
            }
            self.next()
        }) { (error) in
            self.output?.message(text: "Error: \(String(describing: error?.localizedDescription))")
            self.next()
        }
        self.operation?.main()
    }

    func addSession(session:StorageSessionTransport) {
        sessions.append(session)
    }
}
