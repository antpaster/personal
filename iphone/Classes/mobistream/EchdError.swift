//
//  EchdError.swift
//  VideoGorod
//
//  Created by Александр on 18.07.17.
//  Copyright © 2017 Netris. All rights reserved.
//

enum EchdError: Error {
    
    case none
    case notValidUserData
    
    var localizedDescription: String {
        switch self {
        case .none:
            return ""
        case .notValidUserData:
            return "Во время авторизации cервер прислал не валидные данные пользователя."
        }
    }
}
