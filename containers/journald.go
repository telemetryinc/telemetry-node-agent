package containers

import (
	"fmt"

	"github.com/telemetryinc/telemetry-node-agent/logs"
	"github.com/telemetryinc/telemetry-node-agent/proc"
	"github.com/coroot/logparser"
)

var (
	journaldReader *logs.JournaldReader
)

func JournaldInit() error {
	r, err := logs.NewJournaldReader(
		proc.HostPath("/run/log/journal"),
		proc.HostPath("/var/log/journal"),
	)
	if err != nil {
		return err
	}
	journaldReader = r
	return nil
}

func JournaldSubscribe(unit string, ch chan<- logparser.LogEntry) error {
	if journaldReader == nil {
		return fmt.Errorf("journald reader not initialized")
	}
	err := journaldReader.Subscribe(unit, ch)
	if err != nil {
		return err
	}
	return nil
}

func JournaldUnsubscribe(unit string) {
	if journaldReader == nil {
		return
	}
	journaldReader.Unsubscribe(unit)
}
