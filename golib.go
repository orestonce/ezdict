package ezdict

import (
	"context"
	"sync"
)

var gEventCancelFn func()
var gEventCancelFnLocker sync.Mutex

func EventCancel() {
	gEventCancelFnLocker.Lock()
	if gEventCancelFn != nil {
		gEventCancelFn()
		gEventCancelFn = nil
	}
	gEventCancelFnLocker.Unlock()
}

func IsContextCancel(ctx context.Context) bool {
	select {
	case <-ctx.Done():
		return true
	default:
		return false
	}
}

func NewContext() (ctx context.Context, cancelFn context.CancelFunc) {
	ctx, cancelFn = context.WithCancel(context.Background())

	gEventCancelFnLocker.Lock()
	if gEventCancelFn != nil {
		gEventCancelFn()
	}
	gEventCancelFn = cancelFn
	gEventCancelFnLocker.Unlock()
	return ctx, cancelFn
}