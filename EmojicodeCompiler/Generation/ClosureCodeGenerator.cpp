//
//  ClosureCodeGenerator.cpp
//  Emojicode
//
//  Created by Theo Weidmann on 21/08/2017.
//  Copyright © 2017 Theo Weidmann. All rights reserved.
//

#include "ClosureCodeGenerator.hpp"

namespace EmojicodeCompiler {

void ClosureCodeGenerator::declareArguments() {
    FnCodeGenerator::declareArguments();

    captureDestIndex_ = scoper().nextIndex();
    for (auto capture : captures_) {
        scoper().declareVariable(capture.captureId, capture.type).initialize(0);
        captureSize_ += capture.type.size();
    }
}

}  // namespace EmojicodeCompiler
